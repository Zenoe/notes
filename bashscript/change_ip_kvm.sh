#!/bin/bash
# read -p "请输入虚拟机名称:" name
name=
addr=
in_host_name=
gateway=
auto_start=

#!/bin/bash

POSITIONAL=()
while [[ $# -gt 0 ]]
do
key="$1"

case $key in
    -n|--vmname)
    name="$2"
    shift # past argument
    shift # past value
    ;;
    -a|--ipaddress)
    addr="$2"
    shift # past argument
    shift # past value
    ;;
    -g|--gateway)
    gateway="$2"
    echo "gateway is $gateway"
    shift # past argument
    shift # past value
    ;;
    -h|--hostname)
    in_host_name="$2"
    shift # past argument
    shift # past value
    ;;
    -auto)
    auto_start=1
    shift # past argument
    shift # past value
    ;;
    --default)
    DEFAULT=YES
    shift # past argument
    ;;
    *)    # unknown option
    POSITIONAL+=("$1") # save it in an array for later
    shift # past argument
    ;;
esac
done
set -- "${POSITIONAL[@]}" # restore positional parameters


# if [[ -n $1 ]]; then
#     echo "Last line of file specified as non-opt/last argument:"
#     tail -1 "$1"
# fi

if [ -z $name ]; then
    echo "$? name ip"
    exit 1
fi

if [ -z $addr ]; then
    key_num=${name: 1}
    addr="172.29.32.$key_num"
    echo "ip: $addr"
fi

lastfield=$(echo $addr | rev | cut -d. -f1 | rev)
if [ -z $in_host_name ]; then
    in_host_name="hd$lastfield"
    echo "hostname: $in_host_name"
fi

if [ -z $gateway ]; then
    gateway="172.29.32.254"
fi

dev="eth0"
if virsh domstate $name |grep -q running ;then
       echo "修改虚拟机网卡数据,需要关闭虚拟机"
       virsh destroy $name
fi
mountpoint="/media/virtimage"
[ ! -d $mountpoint ] && mkdir $mountpoint
echo "mounting..."
if mount | grep -q "$mountpoint" ;then
       umount $mountpoint
fi
guestmount -d $name -i $mountpoint
if [ $? -ne 0 ]; then
    echo "mount failed"
    exit 1
fi

# read -p "请输入需要修改的网卡名称:" dev
# read -p "请输入IP地址:" addr
#判断原本网卡配置文件中是否有IP地址，有，就修改该IP，没有，就添加一个新的IP地址
if grep -q "IPADDR"  $mountpoint/etc/sysconfig/network-scripts/ifcfg-$dev;then
   sed -i "/IPADDR/s/=.*/=$addr/"  $mountpoint/etc/sysconfig/network-scripts/ifcfg-$dev
   sed -i "/GATEWAY/s/=.*/=$gateway/"  $mountpoint/etc/sysconfig/network-scripts/ifcfg-$dev
else
   echo "IPADDR=$addr" >>  $mountpoint/etc/sysconfig/network-scripts/ifcfg-$dev
   echo "GATEWAY=$gateway" >>  $mountpoint/etc/sysconfig/network-scripts/ifcfg-$dev
fi
#如果网卡配置文件中有客户配置的IP地址，则脚本提示修改IP完成
awk -F= -v x=$addr '$2==x{print "完成..."}' $mountpoint/etc/sysconfig/network-scripts/ifcfg-$dev
guestunmount /media/virtimage

echo "setting hostname"
virt-sysprep -d $name  --hostname $in_host_name --root-password password:123

if [ ! -z "$auto_start" ]; then
echo "starting $name"
virsh start $name
fi

## video server
To serve videos from a specific directory using Nginx, you'll want to create a separate configuration file within the `/etc/nginx/sites-available/` directory and then create a symbolic link to it in the `/etc/nginx/sites-enabled/` directory. Here's how you can do it:

1. **Create a New Configuration File:**
   ```bash
   vi /etc/nginx/sites-available/zenoe_video
   ```
   ```nginx
   server {
       listen 80;
       server_name zenoe.example.com; # Replace with your domain or IP

       location /video/ {
           root /var/www/html/zenoe;
           autoindex on; # Enables directory listing
           add_header Cache-Control 'no-store, no-cache, must-revalidate, proxy-revalidate, max-age=0';
           expires off;
           etag on;
           if_modified_since exact;
           add_header Pragma "no-cache";
           add_header Access-Control-Allow-Origin *; # Allows cross-domain requests if needed
       }

       # Additional location blocks and server configurations can be added here
   }
   ```

   In this configuration, `autoindex on;` allows the listing of the directory contents. If you don't want to list the directory contents, you should turn it off by setting `autoindex off;`.

2. **Enable the Site:**

   Once you've created your configuration file, you need to enable it by creating a symbolic link to it in the `/etc/nginx/sites-enabled/` directory:

   ```bash
   sudo ln -s /etc/nginx/sites-available/zenoe_video /etc/nginx/sites-enabled/
   ```

3. **Test the Configuration:**

   Test to make sure that there are no syntax errors in your Nginx configuration files:

   ```bash
   sudo nginx -t
   ```

   If you get a message saying that the syntax is okay and the test is successful, you can proceed to the next step.

4. **Reload Nginx:**

   To apply the new configuration, reload Nginx:

   ```bash
   sudo systemctl reload nginx
   ```

5. **Verify the Setup:**

   Now, you should be able to access your videos by going to `http://zenoe.example.com/video/` in your web browser. Replace `zenoe.example.com` with your server's domain or IP address.

Remember to replace `/var/www/html/zenoe` with the actual path to your video directory if it's different. Also, ensure that the directory permissions are correctly set so that Nginx can read the files. You might need to adjust the `server_name` directive to match your domain or public IP address. If you're using an IP address or a local network, you can omit the `server_name` directive or replace it with `_`, which is a catch-all.

Please note that serving large video files directly from Nginx is not always the most efficient method for video streaming, especially for large audiences. For streaming to many users, you might want to look into dedicated streaming servers or services that can handle adaptive bitrate streaming and other advanced features.
## 404 trouble shoot
The 404 error indicates that the requested resource was not found on the server. This can happen for several reasons. Let's go through some troubleshooting steps to resolve this issue:

1. **Check the Root Directory**:
   Ensure that the directory `/var/www/html/cbbvideo` exists and contains the files or directories you expect. The path you specified in the `root` directive is crucial. Verify that you have the correct files in the correct location.

   ```bash
   ls -l /var/www/html/cbbvideo
   ```

2. **Verify File Permissions**:
   Ensure that the Nginx process has the necessary permissions to read the files in `/var/www/html/cbbvideo`.

   ```bash
   sudo chown -R www-data:www-data /var/www/html/cbbvideo
   sudo chmod -R 755 /var/www/html/cbbvideo
   ```

   Replace `www-data` with the user and group under which Nginx is running if different.

3. **Nginx Configuration**:
   Ensure your Nginx configuration file is correctly formatted and includes the necessary directives. Here is a sample configuration based on your provided setup:

   ```nginx
   server {
       listen 34444;
       server_name _;

       location /video/ {
           root /var/www/html/cbbvideo;
           autoindex on; # Enables directory listing
           add_header Cache-Control 'no-store, no-cache, must-revalidate, proxy-revalidate, max-age=0';
           expires off;
           etag on;
           if_modified_since exact;
           add_header Pragma "no-cache";
           add_header Access-Control-Allow-Origin *; # Allows cross-domain requests if needed
       }
   }
   ```

4. **Reload Nginx**:
   After making any changes to the Nginx configuration, ensure to reload Nginx to apply the changes:

   ```bash
   sudo nginx -t # Test the configuration for syntax errors
   sudo systemctl reload nginx # Reload Nginx with the new configuration
   ```

5. **Check Nginx Error Logs**:
   Check the Nginx error logs for more details about the 404 error. This can provide more insight into what might be wrong.

   ```bash
   sudo tail -f /var/log/nginx/error.log
   ```

6. **Access URL**:
   Ensure you are accessing the correct URL in your browser. It should be something like `http://your_ip:34444/video/`. Make sure there are files or subdirectories under `/var/www/html/cbbvideo` that can be listed or accessed.

If you follow these steps and everything is configured correctly, you should be able to access the directory and its contents without getting a 404 error. If the problem persists, please provide additional details from the error logs or any other configuration settings that might be relevant.


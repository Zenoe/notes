// python can't encrypt password (can't find a proper way, ModuleNotFoundError: No module named 'Crypto', pip install pycryptodome failed on windows)
// by calling node js' encrypt
// to support password encryption to post to server
const crypto = require('crypto')
const { JSEncrypt } = require('js-encrypt')

const publicKey = `-----BEGIN PUBLIC KEY-----
MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQDNvs/qUMjkfq2E9o0qn03+KJE7
ASczEbn6q+kkthNBdmTsskikWsykpDPnLWhAVkmjz4alQyqw+mHYP9xhx8qUC4A3
tXY0ObxANUUKhUvR7zNj4vk4t8F2nP3erWvaG8J+sN3Ubr40ZYIYLS6UHYRFrqRD
CDhUtyjwERlz8KhLyQIDAQAB
-----END PUBLIC KEY-----`

const privateKey = `-----BEGIN PRIVATE KEY-----
MIICeAIBADANBgkqhkiG9w0BAQEFAASCAmIwggJeAgEAAoGBAM2+z+pQyOR+rYT2
jSqfTf4okTsBJzMRufqr6SS2E0F2ZOyySKRazKSkM+ctaEBWSaPPhqVDKrD6Ydg/
3GHHypQLgDe1djQ5vEA1RQqFS9HvM2Pi+Ti3wXac/d6ta9obwn6w3dRuvjRlghgt
LpQdhEWupEMIOFS3KPARGXPwqEvJAgMBAAECgYADxGqqL7B9/pPOy3TqQuB6tuNx
4SOGm9x76onqUisoF7LhYqJR4Be/LAKHSR2PkATpKvOcMw6lDvCbtQ+j+rSK2PkN
4iDi1RYqbLUbZBS8vhrgU0CPlmgSSp1NBsqMK9265CaJox3frxmBK1yuf22RboIK
pqOzcluuA4aqLegmwQJBAP0+gM/tePzx+53DrxpYQvlfi9UJo7KeqIFL8TjMziKt
EaRGeOZ6UX/r6CQHojYKnNti7pjAwonsdwCTcv1yy7sCQQDP+/ww49VFHErON/MO
w5iYCsrM5Lx+Yc2JAjetCDpkMrRT92cgQ0nxR5+jNeh+gE2AmB9iKlNxsHJoRaPQ
lBRLAkEAl9hiZEp/wStXM8GhvKovfldMAPFGtlNrthtTCDvFXgVoDpgy5f9x3sIU
74WkPcMfSmyHpA/wlcKzmCTRTicHAQJBALUjq7MQ2tAEIgqUo/W52I6i55mnpZsU
pyOqcL8cqW5W0sNGd+SbdizTym8lJkX2jIlw8/RVFLOxjxLNhCzGqx0CQQDeUMnw
7KGP3F7BnbsXCp64YDdihzSO5X/Mfwxw6+S/pyKZ0/X4uwt24kZuoDnFzGWJYlea
sDQC6enIru+ne5es
-----END PRIVATE KEY-----`

// Encrypt with crypto module (RSA - PKCS#1 v1.5 Padding)
var ciphertext = crypto.publicEncrypt(
    {
        key: publicKey,
        padding: crypto.constants.RSA_PKCS1_PADDING
    },
    Buffer.from('The quick brown fox jumps over the lazy dog','utf8')
)
console.log(ciphertext.toString('base64'))

// Decrypt with JSEncrypt
var decrypt = new JSEncrypt()
decrypt.setPrivateKey(privateKey)
var decrypted = decrypt.decrypt(ciphertext.toString('base64'))
console.log(decrypted) // The quick brown fox jumps over the lazy dog

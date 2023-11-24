#rsa公钥与私钥示例
import rsa
import base64
#生成公钥与私钥
(public_key, private_key) = rsa.newkeys(512)
# RSA加密
def rsaEncryption(public_key, cleartext):
	result = rsa.encrypt(cleartext.encode(), public_key)
	return base64.encodebytes(result)

# RSA解密
def rsaDecryption(public_key, ciphertext):
	result = rsa.decrypt(base64.decodebytes(ciphertext), private_key)
	return result.decode()
	
#输出公钥、私钥
print(public_key.save_pkcs1())
print(private_key.save_pkcs1())
cleartext = input("请输入明文:")
ciphertext = rsaEncryption(public_key, cleartext)
print("密文：")
print(ciphertext)
decipher = rsaDecryption(private_key, ciphertext)
print("明文：")
print(decipher)


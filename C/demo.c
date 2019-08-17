#include <stdio.h>
#include <curl/curl.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/md5.h>

int main(void)
{
  CURL *curl;
  CURLcode res;
 
  curl = curl_easy_init();
  if(curl) {
    unsigned char myurl[1000] = "http://api.fanyi.baidu.com/api/trans/vip/translate?";
    unsigned char *appid = "20180926000212405";    //replace myAppid with your own appid
    unsigned char *q = "apple";          //replace apple with your own text to be translate, ensure that the input text is encoded with UTF-8!
    unsigned char *from = "auto";          //replace en with your own language type of input text
    unsigned char *to = "auto";            //replace zh with your own language type of output text
    unsigned char salt[60];
    int a = rand();
    sprintf(salt,"%d",a);
    unsigned char *secret_key = "jdpjDwHibRmfPGd3XiwH";   //replace mySecretKey with your own mySecretKey
    unsigned char sign[120] = "";
    strcat(sign,appid);
    strcat(sign,q);
    strcat(sign,salt);
    strcat(sign,secret_key);
    printf("%s\n",sign);
    unsigned char md[16];
    int i;
    unsigned char tmp[3]={'\0'},buf[33]={'\0'};
    MD5((unsigned char *)sign,strlen((unsigned char *)sign),md);
    for (i = 0; i < 16; i++){
        sprintf(tmp,"%2.2x",md[i]);
        strcat(buf,tmp);
    }
    printf("%s\n",buf);
    strcat(myurl,"appid=");
    strcat(myurl,appid);
    strcat(myurl,"&q=");
    strcat(myurl,q);
    strcat(myurl,"&from=");
    strcat(myurl,from);
    strcat(myurl,"&to=");
    strcat(myurl,to);
    strcat(myurl,"&salt=");
    strcat(myurl,salt);
    strcat(myurl,"&sign=");
    strcat(myurl,buf);
    printf("%s\n",myurl);
    //设置访问的地址
    curl_easy_setopt(curl, CURLOPT_URL, myurl);
    res = curl_easy_perform(curl);
    /* Check for errors */ 
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
 
    /* always cleanup */ 
    curl_easy_cleanup(curl);
  }
  return 0;
}

#include <stdio.h>
#include <curl/curl.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/md5.h>

size_t analysis (char *data, size_t n, size_t l, void* p) {
    printf("%s\n", data);
    printf("%s\n", (char*)p);
    
    return n * l;
}

int Translate (const char *appid, const char *Secretkey, const char *SourceWord, const char *FromLang, const char *ToLang) {
    CURL *curl;
    CURLcode res;
 
    curl = curl_easy_init();
    if (!curl) return 1;
    
    unsigned char myurl[1000] = "http://api.fanyi.baidu.com/api/trans/vip/translate?";
    unsigned char salt[60];
    unsigned char sign[120] = "";
    int a = rand();
    
    sprintf(salt,"%d",a);
    
    strcat(sign, appid);
    strcat(sign, SourceWord);
    strcat(sign, salt);
    strcat(sign, Secretkey);
    printf("-----------------\n");
    printf("%s\n",sign);
    
    unsigned char md[16];
    int i;
    unsigned char tmp[3]={'\0'},buf[33]={'\0'};
    
    MD5((unsigned char *)sign,strlen((unsigned char *)sign),md);
    
    for (i = 0; i < 16; i++){
        sprintf(tmp,"%2.2x",md[i]);
        strcat(buf,tmp);
    }
    
    printf("-----------------\n");
    printf("%s\n",buf);
    
    strcat(myurl, "appid=");
    strcat(myurl, appid);
    strcat(myurl, "&q=");
    strcat(myurl, SourceWord);
    strcat(myurl, "&from=");
    strcat(myurl, FromLang);
    strcat(myurl, "&to=");
    strcat(myurl, ToLang);
    strcat(myurl, "&salt=");
    strcat(myurl, salt);
    strcat(myurl, "&sign=");
    strcat(myurl, buf);
    printf("-----------------\n");
    printf("%s\n",myurl);
    
    //设置访问的地址
    curl_easy_setopt(curl, CURLOPT_URL, myurl);
    
    //FILE *outfile;
    //outfile = fopen("./test.json", "wb");
    //curl_easy_setopt(curl, CURLOPT_WRITEDATA, outfile);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, analysis);
    
    printf("-----------------\n");
    res = curl_easy_perform(curl);
    
    /* Check for errors */ 
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
 
    /* always cleanup */ 
    curl_easy_cleanup(curl);
    //fclose(outfile);
    
    return 0;
}


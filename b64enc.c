#include <stdint.h>
#include <stdio.h>
#include <windows.h>

int main(int argc,char *argv[]){
  FILE *fin,*fout;
  char base64chars[]="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
  uint8_t chars=0,c=0,in_b[4],out_b[4];
  if(argc==3){
    fin=fopen(argv[1],"rb");
    if(fin){
      fout=fopen(argv[2],"w");
      if(fout){
        for(;;){
          *(uint32_t*)in_b=0x00000000;
          *(uint32_t*)out_b=0x3d3d3d3d;
          if((chars=fread(in_b,1,3,fin))){
            out_b[0]=base64chars[in_b[0]>>2];
            out_b[1]=base64chars[((in_b[0]&0x03)<<4)|(in_b[1]>>4)];
            if(chars>1){
              out_b[2]=base64chars[((in_b[1]&0x0f)<<2)|(in_b[2]>>6)];
              if(chars>2) out_b[3]=base64chars[in_b[2]&0x3f];
            };
            if(fwrite(out_b,1,4,fout)<4) break;
            if((c+=4)==64){
              if(fputc(10,fout)==EOF) break;
              c=0;
            };
          }
          else break;
        };
      };
    };
    fcloseall();
  };
  return 0;
}

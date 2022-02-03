#include <stdio.h>

int main(int argc, char *argv[]){
  FILE *fin,*fout;
  char in_b[4],out_b[3],s,base64[]="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/",unbase64[0xff];
  int c;
  if(argc==3){
    fin=fopen(argv[1],"rb");
    if(fin){
      fout=fopen(argv[2],"wb");
      if(fout){
        for(c=0;c<0xff;c++) unbase64[c]=-1;
        for(c=0;c<64;c++) unbase64[base64[c]]=c;
        c=0;
        for(;;){
          if(c<4){
            if((in_b[c]=fgetc(fin))==EOF){
              c=0;
              break;
            };
            if((in_b[c]==10)||(in_b[c]==13)) c--;
            c++;
            continue;
          };
          c=0;
          if((s=unbase64[(uint8_t)in_b[0]])>=0){
            out_b[c]=s<<2;
            if((s=unbase64[(uint8_t)in_b[1]])>=0){
              out_b[c++]|=s>>4;
              out_b[c]=s<<4;
              if((s=unbase64[(uint8_t)in_b[2]])>=0){
                out_b[c++]|=s>>2;
                out_b[c++]=s<<6;
                if((s=unbase64[(uint8_t)in_b[3]])>=0){
                  out_b[c-1]|=s;
                  if(fwrite(out_b,1,c,fout)<c) break;
                  c=0;
                  continue;
                };
              };
            };
          };
          break;
        };
        fwrite(out_b,1,c,fout);
      };
      fcloseall();
    };
  };
  return 0;
}

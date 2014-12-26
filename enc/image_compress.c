/*
simple and fast functions for loseless image compression
26.12.2014 - initial version, only simple type 1 (offset compress with fast forward) 24 bit RGB image compress
*/
#include <stdint.h> // todo remove
 
//
uint32_t compress_type_1_RGB_24(char *in_buffer,char *out_buffer,uint32_t len){
uint32_t out_count=0;
uint32_t in_count=0;
uint32_t i,j,k,l,found_index; 
//parameters for fine tune

const int fast_f=10; // max fast forward bytes not to compress.
const int ext_size=0;// extended bytes offset 0- off, 1- one byte add to offset, 2- two bytes...
const int skip_f=3;  // skip format bytes - 24 bit color means 3 bytes	
const int max_offset=255-(fast_f+ext_size)+255*ext_size; // max offset for search

	for(i=0;i<len/skip_f;i++){
		found_index=0;
		for(j=0;j<max_offset;j++){
			for(k=0;k<fast_f;k++)	{
				if(k+i*skip_f<len)	{ //main search - match 3 bytes only
					if(in_buffer[(i-j+k)*skip_f]==in_buffer[(i+k)*skip_f]&&
					   in_buffer[(i-j+k)*skip_f+1]==in_buffer[(i+k)*skip_f+1]&&
					   in_buffer[(i-j+k)*skip_f+2]==in_buffer[(i+k)*skip_f+2] ){
						found_index=j;
						break;
					}
				}
			if(found_index)	break;
			}
			if(k){ // we need to copy fast forward bytes
				for(l=0;l<k*skip_f;l++)
					out_buffer[out_count++]=in_buffer[in_count++];
				i+=k; //todo remove
			}
			if(found_index)	{ //record only index 3:1 ratio
				out_buffer[in_count++]=found_index;
				i++; //todo remove
				break;
			}
		}
	}


}
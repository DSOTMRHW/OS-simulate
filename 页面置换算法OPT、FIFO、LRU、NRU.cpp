#include<stdio.h>
int main()
{
	int a[20] = {7,0,1,2,0,3,0,4,2,3,0,3,2,1,2,0,1,7,0,1};
	int b[3] = {0};
	int c = 0;
	int r[3] = {0,0,0};
	int max = 99;
	int v[3] = {1};
	int optflag[3] = {0,0,0};
	
////FIFO
//	c = 0;
//	for(int i=0;i<20;i++){
//		if(i<3){
//			b[c] = a[i];
//			c = (c+1)%3;
//		}
//		if(b[0]==a[i]){
//			continue;
//		}
//		if(b[1]==a[i]){
//			continue;
//		}
//		if(b[2]==a[i]){
//			continue;
//		}
//		if(i>2 && b[c] != a[i]){
//			b[c] = a[i];
//			c = (c+1)%3;
////			printf("%d%d%d\n",b[0],b[1],b[2]);
////			printf("%d\n",a[i]);
//		}
//	}

////LRU
//	c = 0;
//	for(int i=0;i<20;i++){
//		if(i<3){
//			b[c] = a[i];
//			c = (c+1)%3;
//			if(i==2){
//				r[0]=2;
//				r[1]=1;
//				r[2]=0;
//			}
//		}
//		if(i>2){
//			if(b[0]==a[i]){
//				r[0]=0;
//				r[1]++;
//				r[2]++;
//			}
//			else if(b[1]==a[i]){
//				r[1]=0;
//				r[0]++;
//				r[2]++;
//			}
//			else if(b[2]==a[i]){
//				r[2]=0;
//				r[1]++;
//				r[0]++;
//			}
//			else{
//				max = 0;
//				max=(r[0]>r[1])?0:1;
//				max=(r[max]>r[2])?max:2;
//				b[max] = a[i];
//				r[(max+1)%3]++;
//				r[(max+2)%3]++;
//				printf("%d\n",a[i]);
//				printf("%d%d%d\n",b[0],b[1],b[2]);
//				
//				r[max] = 0;
//				max = 0;
//			}
//		}
//	}

////NRU
//	c = 0;
//	for(int i=0;i<20;i++){
//		if(i<3){
//			b[i] = a[i];
//			v[i] = 1;
//		}
//		if(i>2){
//			if(a[i] == b[0]){
//				v[0] = 1;
//				c = (c+1)%3;
//				continue;
//			}
//			if(a[i] == b[1]){
//				v[1] = 1;
//			c = (c+1)%3;
//			continue;
//			}
//			if(a[i] == b[2]){
//				v[2] = 1;
//			c = (c+1)%3;
//			continue;
//			}
//			
//			while(v[c] == 1){
//				v[c]--;
//				c = (c+1)%3;
//			}
//			if(v[c] == 0){
//				b[c] = a[i];
//				printf("%d%d%d\n",b[0],b[1],b[2]);
//				printf("%d\n",a[i]);
//				v[c] = 1;
//				c = (c+1)%3;
//			}
//		}
//	}

//opt
	c = 0;
	for(int i=0;i<20;i++){
		if(i<3){
			b[c] = a[i];
			c = (c+1)%3;
		}
		if(b[0]==a[i]){
			continue;
		}
		if(b[1]==a[i]){
			continue;
		}
		if(b[2]==a[i]){
			continue;
		}
		else{
			r[0]=99;
			r[1]=99;
			r[2]=99;
			for(int j=i;j<20;j++){            //找寄存器里面最远下次遇到的
				if(b[0]==a[j]){
					if(optflag[0] == 1){
						continue;
					}
					r[0] = j;
					optflag[0] = 1;
					continue;
				}
				if(b[1]==a[j]){
					if(optflag[1] == 1){
						continue;
					}
					r[1] = j;
					optflag[1] = 1;
					continue;
				}
				if(b[2]==a[j]){
					if(optflag[2] == 1){
						continue;
					}
					r[2] = j;
					optflag[2] = 1;
					continue;
				}
			}
			max = 0;
			max=(r[0]>r[1])?0:1;
			max=(r[max]>r[2])?max:2;
			b[max] = a[i];
			printf("%d\n",a[i]);
			printf("%d%d%d\n",b[0],b[1],b[2]);
			optflag[0] = 0;
			optflag[1] = 0;
			optflag[2] = 0;
		}
	}
	return 0;
}

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>

typedef struct fbdev{
    int fdfd; //open "dev/fb0"
    struct fb_var_screeninfo vinfo;
    struct fb_fix_screeninfo finfo;
    long int screensize;
    char *map_fb; 
    
}FBDEV;

unsigned short int color = 65535;

void init_dev(FBDEV *dev)
{
    FBDEV *fr_dev=dev;

    fr_dev->fdfd=open("/dev/fb0",O_RDWR);
    printf("the framebuffer device was opended successfully.\n");

    ioctl(fr_dev->fdfd,FBIOGET_FSCREENINFO,&(fr_dev->finfo)); //获取 固定参数

    ioctl(fr_dev->fdfd,FBIOGET_VSCREENINFO,&(fr_dev->vinfo)); //获取可变参数
	printf("width:%d\theight:%d\n", fr_dev->vinfo.xres, fr_dev->vinfo.yres);
	printf("width_virtual:%d\theight_virtual:%d\n", fr_dev->vinfo.xres_virtual, fr_dev->vinfo.yres_virtual);

    fr_dev->screensize=fr_dev->vinfo.xres*fr_dev->vinfo.yres*fr_dev->vinfo.bits_per_pixel/8; 

    fr_dev->map_fb=(char *)mmap(NULL,fr_dev->screensize,PROT_READ|PROT_WRITE,MAP_SHARED,fr_dev->fdfd,0);

    printf("init_dev successfully.\n");
}

void draw_dot(FBDEV *dev,int x,int y) //(x.y) 是坐标
{
    FBDEV *fr_dev=dev;
    int *xx=&x;
    int *yy=&y;    

    long int location=0;
    location=location=(*xx+fr_dev->vinfo.xoffset)*(fr_dev->vinfo.bits_per_pixel/8)+
                 (*yy+fr_dev->vinfo.yoffset)*fr_dev->finfo.line_length;
    int b=10;
    int g=10;
    int r=10;
    unsigned short int t=color;
    *((unsigned short int *)(fr_dev->map_fb+location))=t;
}


void draw_line(FBDEV *dev,int x1,int y1,int x2,int y2) 
{
    FBDEV *fr_dev=dev;
    int *xx1=&x1;
    int *yy1=&y1;
    int *xx2=&x2;
    int *yy2=&y2;

    int i=0;
    int j=0;
    int tekxx=*xx2-*xx1;
    int tekyy=*yy2-*yy1;
	if (tekxx == 0 || tekyy == 0)
	{
		return;
	}
    //if((*xx2>=*xx1)&&(*yy2>=*yy1))
    if(*xx2>=*xx1)
    {    
        for(i=*xx1;i<=*xx2;i++)
        {
            j=(i-*xx1)*tekyy/tekxx+*yy1;
            draw_dot(fr_dev,i,j);
        }
    }
    else
    {
        //if(*xx2<*xx1)
        for(i=*xx2;i<*xx1;i++)
        {
            j=(i-*xx2)*tekyy/tekxx+*yy2;
            draw_dot(fr_dev,i,j);
        }
    }


}

void draw_rect(FBDEV *dev,int x1,int y1,int x2,int y2)
{
    FBDEV *fr_dev=dev;
    int *xx1=&x1;
    int *yy1=&y1;
    int *xx2=&x2;
    int *yy2=&y2;
    int i=0,j=0;
   
    for(j=*yy1;j<*yy2;j++) //注意 这里要 xx1 < xx2
        for(i=*xx1;i<*xx2;i++)
        {
            draw_dot(fr_dev,i,j);            
        }
    
}

void clear(FBDEV *dev)
{
	FBDEV *fr_dev=dev;
	memset(fr_dev->map_fb, 0x00, fr_dev->screensize);
}
int main()
{
    FBDEV     fr_dev;
    fr_dev.fdfd=-1;
    init_dev(&fr_dev);
   
    int x = 0;
	float phase=0.0f;
	int y = 0;
	int prev_x = 0;
	int prev_y = 0;
	while(phase < 3.14159*20)
	{
		clear(&fr_dev);
		for (x=0;x<480;x++)
		{
			y = (sin(phase+2*3.1415*x/240.0) + 1.0) * 120 + 10;
			// draw_dot(&fr_dev,x,y);
			// draw_rect(&fr_dev,x,y,x+1,y+1);
			draw_line(&fr_dev, prev_x, prev_y, x, y);
			prev_x = x;
			prev_y = y;
		}
		usleep(5000);
		phase+=0.1f;
	}
	draw_line(&fr_dev,0,0,100,100);
	draw_line(&fr_dev,200,200,110,110);
	draw_line(&fr_dev,10,200,150,100);
	draw_line(&fr_dev,300,10,160,90);
	draw_rect(&fr_dev,300,200,320,240);
	draw_rect(&fr_dev,470,262,479,271);
	
    
    printf("bye the framebuffer\n");
    munmap(fr_dev.map_fb,fr_dev.screensize);
    close(fr_dev.fdfd);
    
    return 0;    
}
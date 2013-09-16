#include<stdio.h>
#include<cv.h>
#include<cvaux.h>
#include<highgui.h>
#include<math.h>
#include<windows.h>


#define uchar unsigned char
#define uint unsigned int



#define DEC 320

	double fps = 20;

	char flagx = 0;
//用来遍历图像的循环计数量
	int x,y;	
	int i,j,k;
	int notfound = 0;
	int start = 0;
	int lhb = 1;
	int widthflag = 0;
	int on = 0;

	int found = 0;
	int oning = 0;
	bool foundornot = 0;
	bool oningornot = 0;

	int mid1 = 320;
	int mid2 = 320;
	int mid3 = 320;
	int mid4 = 320;

	bool flag1 = 1;
	bool flag2 = 1;
	bool flag3 = 1;
	bool flag4 = 1;
	bool flag5 = 1;

	bool _BGR = 0;
	bool _BRG = 0;
	bool _GBR = 0;
	bool _GRB = 0;
	bool _RBG = 0;
	bool _RGB = 0;
	bool ok = 0;

	int b_num=0, g_num=0, r_num=0;

	int com = 8;

	double b_y = 0;
	double g_y = 0;
	double r_y = 0;

#ifdef _NEW_THRED_
#define _NEW_THRED_	
int thred_r_h_h = 255;
int thred_r_h_l = 0;
int thred_r_b_l = 0;
int thred_r_b_h = 210;
int thred_r_g_l = 0;
int thred_r_g_h = 210;
int thred_r_r_l = 120;
int thred_r_r_h = 255;
int thred_r_s_h = 255;
int thred_r_s_l = 50;
int thred_r_v_h = 255;
int thred_r_v_l = 172;

int thred_g_h_h = 95;
int thred_g_h_l = 60;
int thred_g_b_l = 0;
int thred_g_b_h = 255;
int thred_g_g_l = 50;
int thred_g_g_h = 255;
int thred_g_r_l = 0;
int thred_g_r_h = 193;
int thred_g_s_h = 255;
int thred_g_s_l = 70;
int thred_g_v_h = 255;
int thred_g_v_l = 47;

int thred_b_h_h = 128;
int thred_b_h_l = 100;
int thred_b_b_l = 25;
int thred_b_b_h = 255;
int thred_b_g_l = 0;
int thred_b_g_h = 180;
int thred_b_r_l = 0;	
int thred_b_r_h = 160;
int thred_b_s_h = 255;
int thred_b_s_l = 130;
int thred_b_v_h = 255;
int thred_b_v_l = 80;
#else
int thred_r_h_h = 255;
int thred_r_h_l = 0;
int thred_r_b_l = 0;
int thred_r_b_h = 160;
int thred_r_g_l = 0;
int thred_r_g_h = 160;
int thred_r_r_l = 120;
int thred_r_r_h = 255;
int thred_r_s_h = 255;
int thred_r_s_l = 115;
int thred_r_v_h = 255;
int thred_r_v_l = 125;

int thred_g_h_h = 95;
int thred_g_h_l = 60;
int thred_g_b_l = 0;
int thred_g_b_h = 255;
int thred_g_g_l = 50;
int thred_g_g_h = 255;
int thred_g_r_l = 0;
int thred_g_r_h = 143;
int thred_g_s_h = 255;
int thred_g_s_l = 130;
int thred_g_v_h = 255;
int thred_g_v_l = 47;

int thred_b_h_h = 128;
int thred_b_h_l = 105;
int thred_b_b_l = 25;
int thred_b_b_h = 255;
int thred_b_g_l = 0;
int thred_b_g_h = 180;
int thred_b_r_l = 0;	
int thred_b_r_h = 160;
int thred_b_s_h = 255;
int thred_b_s_l = 130;
int thred_b_v_h = 255;
int thred_b_v_l = 0;
#endif
#ifdef _OLD_CAM_
#define _OLD_CAM_
	int b_hsv_l = 99;
	int b_hsv_h = 114;
	int thred_b_b_l = 160;
	int thred_b_b_h = 255;
	int thred_b_g_l = 0;
	int thred_b_g_h = 144;
	int thred_b_r_l = 0;
	int thred_b_r_h = 33;

	int g_hsv_l = 70;
	int g_hsv_h = 87;
	int thred_g_b_l = 64;
	int thred_g_b_h = 232;
	int thred_g_g_l = 148;
	int thred_g_g_h = 255;
	int thred_g_r_l = 0;
	int thred_g_r_h = 65;

	int r_hsv_l = 0;
	int r_hsv_h = 181;
	int thred_r_b_l = 0;
	int thred_r_b_h = 178;
	int thred_r_g_l = 0;
	int thred_r_g_h = 120;
	int thred_r_r_l = 140;
	int thred_r_r_h = 255;
#endif

	//IplImage* result;

	CvSize g_size;
//函数声明
	void myHandle(IplImage *src, IplImage* frame);
	//dat可以是：
	//0x66 ------ b
	//int a = 102	----- b  (0x66的十进制数）
	//uchar a = 0x66	----- b
	int sentToUART(uchar dat, int comnum);
//	void get_loc_rec(IplImage *src);
	void getloc(IplImage *frame, IplImage* hue, int bgr);
	bool B(uchar* frame_ptr, uchar* hsv_ptr, int pos);
	bool G(uchar* frame_ptr, uchar* hsv_ptr, int pos);
	bool R(uchar* frame_ptr, uchar* hsv_ptr, int pos);
//主函数
int main(int argc, char** argv)
{
	IplImage* frame;
	CvCapture* capture;	
	uint key = 0;
	IplImage* hsv;
	cvNamedWindow("frame");
	capture = cvCaptureFromCAM(1);
	//capture = cvCaptureFromFile("d://5/r.avi");
	CvSize size = cvSize((int )cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH),
	(int)cvGetCaptureProperty( capture, CV_CAP_PROP_FRAME_HEIGHT));
	CvVideoWriter * writer;
	if(argc == 3)
		writer = cvCreateVideoWriter(argv[2], CV_FOURCC('M','J','P','G'), fps, size, 1);

	frame = cvQueryFrame(capture);
	//frame = cvLoadImage("d://2/a.jpg");
	flagx = argv[1][0];
	if(argv[1][0] == '2')
	{
		flag1 = 0;
//		flag22 = 1;
	}
	if(argv[1][0] == '3')
	{
		flag1 = 0;
		flag2 = 0;
	}
	if(argv[1][0] == '4')
	{
		flag1 = 0;
		flag2 = 0;
		flag3 = 0;
	}
	g_size = cvGetSize(frame);
	hsv = cvCreateImage(g_size, 8, 3);
	while(1)
	{
		//time1 = GetTickCount();
		frame = cvQueryFrame(capture);
		if(argc == 3)
		{//printf("hello");
			cvWriteFrame(writer, frame);
		}
		if(flag3 == 0)
		{
thred_r_h_h = 255;
thred_r_h_l = 0;
thred_r_b_l = 0;
thred_r_b_h = 210;
thred_r_g_l = 0;
thred_r_g_h = 210;
thred_r_r_l = 120;
thred_r_r_h = 255;
thred_r_s_h = 255;
thred_r_s_l = 50;
thred_r_v_h = 255;
thred_r_v_l = 172;

thred_g_h_h = 95;
thred_g_h_l = 60;
thred_g_b_l = 0;
thred_g_b_h = 255;
thred_g_g_l = 50;
thred_g_g_h = 255;
thred_g_r_l = 0;
thred_g_r_h = 193;
thred_g_s_h = 255;
thred_g_s_l = 70;
thred_g_v_h = 255;
thred_g_v_l = 47;

thred_b_h_h = 128;
thred_b_h_l = 100;
thred_b_b_l = 25;
thred_b_b_h = 255;
thred_b_g_l = 0;
thred_b_g_h = 180;
thred_b_r_l = 0;	
thred_b_r_h = 160;
thred_b_s_h = 255;
thred_b_s_l = 130;
thred_b_v_h = 255;
thred_b_v_l = 80;
		}
		
		cvCvtColor(frame, hsv, CV_BGR2HSV);
		myHandle(frame, hsv);
//1 bgr	2 brg	3 gbr 4 grb	5 rbg 6 rgb
		cvShowImage("frame", frame);
		key = cvWaitKey(6);
		if(key==27)				//按esc退出
		{	
			return 0;
		}
		//printf("%d\n", GetTickCount()-time1);
	}
	cvReleaseCapture(&capture);
	return 0;
}

void myHandle(IplImage *frame, IplImage * hsv)
{
	//1 bgr	2 brg	3 gbr 4 grb	5 rbg 6 rgb
	if(flag1)
	{
		if(lhb == 1)
		{
			sentToUART(0xf1, com);	//阶段1开始
			cvWaitKey(10);
			sentToUART(0xf1, com);
			cvWaitKey(10);
			sentToUART(0xf1, com);
			cvWaitKey(10);
			sentToUART(0xf1, com);
			cvWaitKey(10);
			sentToUART(0xf1, com);
			cvWaitKey(10);
			sentToUART(0xf1, com);
			cvWaitKey(10);
			sentToUART(0xf1, com);
			cvWaitKey(10);
			sentToUART(0xf1, com);
			cvWaitKey(10);
			sentToUART(0xf1, com);
			cvWaitKey(10);
			sentToUART(0xf1, com);
			cvWaitKey(10);
			sentToUART(0xf1, com);
			cvWaitKey(10);
			sentToUART(0xf1, com);
			cvWaitKey(10);
			sentToUART(0xf1, com);
			cvWaitKey(10);
			sentToUART(0xf1, com);
			cvWaitKey(10);
			sentToUART(0xf1, com);
			cvWaitKey(10);
			sentToUART(0xf1, com);
			cvWaitKey(10);
			sentToUART(0xf1, com);
			cvWaitKey(10);
			sentToUART(0xf1, com);
			cvWaitKey(10);
			sentToUART(0xf1, com);
			cvWaitKey(10);
			sentToUART(0xf1, com);
			cvWaitKey(10);
			sentToUART(0xf1, com);
			cvWaitKey(10);
			sentToUART(0xf1, com);
			cvWaitKey(10);
			sentToUART(0xf1, com);
			cvWaitKey(10);
			sentToUART(0xf1, com);
			cvWaitKey(10);
			sentToUART(0xf1, com);
			cvWaitKey(10);
			sentToUART(0xf1, com);
			cvWaitKey(10);
			sentToUART(0xf1, com);
			cvWaitKey(10);
			sentToUART(0xf1, com);
			cvWaitKey(10);
			sentToUART(0xf1, com);
			cvWaitKey(10);
			sentToUART(0xf1, com);
			cvWaitKey(10);
			sentToUART(0xf1, com);
			cvWaitKey(10);
			sentToUART(0xf1, com);
			cvWaitKey(10);
			sentToUART(0xf1, com);
			cvWaitKey(10);
			sentToUART(0xf1, com);
			cvWaitKey(10);
			sentToUART(0xf1, com);
			cvWaitKey(10);
			sentToUART(0xf1, com);
			cvWaitKey(10);
			sentToUART(0xf1, com);
			lhb = 0;
			start = 0;
			printf("/t/t1\n");
		}
	//	printf("hello");
		getloc(frame, hsv, 4);
	}
	else if(flag2)
	{
		/*if(flagx == '2')
		{
			lhb = 0;
			flagx = 0;
		}*/
		if(flagx == '2')
		{
			sentToUART(0xf0, com);
			cvWaitKey(10);
			sentToUART(0xf0, com);
			cvWaitKey(10);
			sentToUART(0xf0, com);
			cvWaitKey(10);
			sentToUART(0xf0, com);
			cvWaitKey(10);
			sentToUART(0xf0, com);
			cvWaitKey(10);
			sentToUART(0xf0, com);
			cvWaitKey(10);
			sentToUART(0xf0, com);
			cvWaitKey(10);
			sentToUART(0xf0, com);
			cvWaitKey(10);
			sentToUART(0xf0, com);
			cvWaitKey(10);
			sentToUART(0xf0, com);
			cvWaitKey(10);
			sentToUART(0xf0, com);
			cvWaitKey(10);
			sentToUART(0xf0, com);
			cvWaitKey(10);
			sentToUART(0xf0, com);
			cvWaitKey(10);
			sentToUART(0xf0, com);
			cvWaitKey(10);
			sentToUART(0xf0, com);
			cvWaitKey(10);
			sentToUART(0xf0, com);
			cvWaitKey(10);
			sentToUART(0xf0, com);
			cvWaitKey(10);
			sentToUART(0xf0, com);
			cvWaitKey(10);
			sentToUART(0xf0, com);
			cvWaitKey(10);
			sentToUART(0xf0, com);
			cvWaitKey(10);
			sentToUART(0xf0, com);
			cvWaitKey(10);
			sentToUART(0xf0, com);
			cvWaitKey(10);
			sentToUART(0xf0, com);
			cvWaitKey(10);
			sentToUART(0xf0, com);
			cvWaitKey(10);
			sentToUART(0xf0, com);
			cvWaitKey(10);
			sentToUART(0xf0, com);
			cvWaitKey(10);
			sentToUART(0xf0, com);
			cvWaitKey(10);
			sentToUART(0xf0, com);
			cvWaitKey(10);
			sentToUART(0xf0, com);
			cvWaitKey(10);
			sentToUART(0xf0, com);
			cvWaitKey(10);
			sentToUART(0xf0, com);
			cvWaitKey(10);
			sentToUART(0xf0, com);
			cvWaitKey(10);
			sentToUART(0xf0, com);
			cvWaitKey(10);
			sentToUART(0xf0, com);
			cvWaitKey(10);
			sentToUART(0xf0, com);
			cvWaitKey(10);
			sentToUART(0xf0, com);
			cvWaitKey(10);
			sentToUART(0xf0, com);
			flagx = 0;
			printf("/t/t0\n");
			lhb = 1;
		}
			
		if(lhb == 0)
		{
			sentToUART(0xf2, com);
			cvWaitKey(10);
			sentToUART(0xf2, com);
			cvWaitKey(10);
			sentToUART(0xf2, com);
			cvWaitKey(10);
			sentToUART(0xf2, com);
			cvWaitKey(10);
			sentToUART(0xf2, com);
			cvWaitKey(10);
			sentToUART(0xf2, com);
			cvWaitKey(10);
			sentToUART(0xf2, com);
			cvWaitKey(10);
			sentToUART(0xf2, com);
			cvWaitKey(10);
			sentToUART(0xf2, com);
			cvWaitKey(10);
			sentToUART(0xf2, com);
			cvWaitKey(10);
			sentToUART(0xf2, com);
			cvWaitKey(10);
			sentToUART(0xf2, com);
			cvWaitKey(10);
			sentToUART(0xf2, com);
			cvWaitKey(10);
			sentToUART(0xf2, com);
			cvWaitKey(10);
			sentToUART(0xf2, com);
			cvWaitKey(10);
			sentToUART(0xf2, com);
			cvWaitKey(10);
			sentToUART(0xf2, com);
			cvWaitKey(10);
			sentToUART(0xf2, com);
			cvWaitKey(10);
			sentToUART(0xf2, com);
			cvWaitKey(10);
			sentToUART(0xf2, com);
			cvWaitKey(10);
			sentToUART(0xf2, com);
			cvWaitKey(10);
			sentToUART(0xf2, com);
			cvWaitKey(10);
			sentToUART(0xf2, com);
			cvWaitKey(10);
			sentToUART(0xf2, com);
			cvWaitKey(10);
			sentToUART(0xf2, com);
			cvWaitKey(10);
			sentToUART(0xf2, com);
			cvWaitKey(10);
			sentToUART(0xf2, com);
			cvWaitKey(10);
			sentToUART(0xf2, com);
			cvWaitKey(10);
			sentToUART(0xf2, com);
			cvWaitKey(10);
			sentToUART(0xf2, com);
			cvWaitKey(10);
			sentToUART(0xf2, com);
			cvWaitKey(10);
			sentToUART(0xf2, com);
			cvWaitKey(10);
			sentToUART(0xf2, com);
			cvWaitKey(10);
			sentToUART(0xf2, com);
			cvWaitKey(10);
			sentToUART(0xf2, com);
			cvWaitKey(10);
			sentToUART(0xf2, com);
			cvWaitKey(10);
			sentToUART(0xf2, com);
			lhb = 1;
			start = 0;
			printf("\t\t2\n");
		}
		getloc(frame, hsv, 1);
	}
	else if(flag3)
	{
		if(flagx == '3')
		{
			lhb = 1;
			flagx = 0;
		}
		if(lhb == 1)
		{
			sentToUART(0xf3, com);
			cvWaitKey(10);
			sentToUART(0xf3, com);
			cvWaitKey(10);
			sentToUART(0xf3, com);
			cvWaitKey(10);
			sentToUART(0xf3, com);
			cvWaitKey(10);
			sentToUART(0xf3, com);
			cvWaitKey(10);
			sentToUART(0xf3, com);
			cvWaitKey(10);
			sentToUART(0xf3, com);
			cvWaitKey(10);
			sentToUART(0xf3, com);
			cvWaitKey(10);
			sentToUART(0xf3, com);
			cvWaitKey(10);
			sentToUART(0xf3, com);
			cvWaitKey(10);
			sentToUART(0xf3, com);
			cvWaitKey(10);
			sentToUART(0xf3, com);
			cvWaitKey(10);
			sentToUART(0xf3, com);
			cvWaitKey(10);
			sentToUART(0xf3, com);
			cvWaitKey(10);
			sentToUART(0xf3, com);
			cvWaitKey(10);
			sentToUART(0xf3, com);
			cvWaitKey(10);
			sentToUART(0xf3, com);
			cvWaitKey(10);
			sentToUART(0xf3, com);
			cvWaitKey(10);
			sentToUART(0xf3, com);
			cvWaitKey(10);
			sentToUART(0xf3, com);
			cvWaitKey(10);
			sentToUART(0xf3, com);
			cvWaitKey(10);
			sentToUART(0xf3, com);
			cvWaitKey(10);
			sentToUART(0xf3, com);
			cvWaitKey(10);
			sentToUART(0xf3, com);
			cvWaitKey(10);
			sentToUART(0xf3, com);
			cvWaitKey(10);
			sentToUART(0xf3, com);
			cvWaitKey(10);
			sentToUART(0xf3, com);
			cvWaitKey(10);
			sentToUART(0xf3, com);
			cvWaitKey(10);
			sentToUART(0xf3, com);
			cvWaitKey(10);
			sentToUART(0xf3, com);
			cvWaitKey(10);
			sentToUART(0xf3, com);
			cvWaitKey(10);
			sentToUART(0xf3, com);
			cvWaitKey(10);
			sentToUART(0xf3, com);
			cvWaitKey(10);
			sentToUART(0xf3, com);
			cvWaitKey(10);
			sentToUART(0xf3, com);
			cvWaitKey(10);
			sentToUART(0xf3, com);
			cvWaitKey(10);
			sentToUART(0xf3, com);
			lhb = 0;
			start = 0;
			printf("\t\t3\n");
		}
		getloc(frame, hsv, 6);
	}
	else if(flag4)
	{
		if(flagx == '4')
		{
			lhb = 0;
			flagx = 0;
		}
		if(lhb == 0)
		{
			printf("\t\t4\n");
			sentToUART(0xf4, com);
			//sentToUART(0xf2, com);
			cvWaitKey(10);
			sentToUART(0xf4, com);
			cvWaitKey(10);
			sentToUART(0xf4, com);
			cvWaitKey(10);
			sentToUART(0xf4, com);
			cvWaitKey(10);
			sentToUART(0xf4, com);
			cvWaitKey(10);
			sentToUART(0xf4, com);
			cvWaitKey(10);
			sentToUART(0xf4, com);
			cvWaitKey(10);
			sentToUART(0xf4, com);
			cvWaitKey(10);
			sentToUART(0xf4, com);
			cvWaitKey(10);
			sentToUART(0xf4, com);
			cvWaitKey(10);
			sentToUART(0xf4, com);
			cvWaitKey(10);
			sentToUART(0xf4, com);
			cvWaitKey(10);
			sentToUART(0xf4, com);
			cvWaitKey(10);
			sentToUART(0xf4, com);
			cvWaitKey(10);
			sentToUART(0xf4, com);
			cvWaitKey(10);
			sentToUART(0xf4, com);
			cvWaitKey(10);
			sentToUART(0xf4, com);
			cvWaitKey(10);
			sentToUART(0xf4, com);
			cvWaitKey(10);
			sentToUART(0xf4, com);
			cvWaitKey(10);
			sentToUART(0xf4, com);
			cvWaitKey(10);
			sentToUART(0xf4, com);
			cvWaitKey(10);
			sentToUART(0xf4, com);
			cvWaitKey(10);
			sentToUART(0xf4, com);
			cvWaitKey(10);
			sentToUART(0xf4, com);
			cvWaitKey(10);
			sentToUART(0xf4, com);
			cvWaitKey(10);
			sentToUART(0xf4, com);
			cvWaitKey(10);
			sentToUART(0xf4, com);
			cvWaitKey(10);
			sentToUART(0xf4, com);
			cvWaitKey(10);
			sentToUART(0xf4, com);
			cvWaitKey(10);
			sentToUART(0xf4, com);
			cvWaitKey(10);
			sentToUART(0xf4, com);
			cvWaitKey(10);
			sentToUART(0xf4, com);
			cvWaitKey(10);
			sentToUART(0xf4, com);
			cvWaitKey(10);
			sentToUART(0xf4, com);
			cvWaitKey(10);
			sentToUART(0xf4, com);
			cvWaitKey(10);
			sentToUART(0xf4, com);
			cvWaitKey(10);
			sentToUART(0xf4, com);

			lhb = 1;
			start = 0;
		}
		getloc(frame, hsv, 5);
	}
}

bool B(uchar* frame_ptr, uchar* hsv_ptr, int pos)
{
	if( hsv_ptr[3*pos+0]     >=thred_b_h_l && hsv_ptr[3*pos+0]  <=thred_b_h_h
		&& hsv_ptr[3*pos+1]  >=thred_b_s_l && hsv_ptr[3*pos+1]  <=thred_b_s_h
		&& hsv_ptr[3*pos+2]  >=thred_b_v_l && hsv_ptr[3*pos+2]  <=thred_b_v_h
		&& frame_ptr[3*pos+0]>=thred_b_b_l && frame_ptr[3*pos+0]<=thred_b_b_h
		&& frame_ptr[3*pos+1]>=thred_b_g_l && frame_ptr[3*pos+1]<=thred_b_g_h
		&& frame_ptr[3*pos+2]>=thred_b_r_l && frame_ptr[3*pos+2]<=thred_b_r_h
		)
		return TRUE;
	else
		return FALSE;
}
bool G(uchar* frame_ptr, uchar* hsv_ptr, int pos)
{
	if(frame_ptr[3*pos+0]    >=thred_g_b_l && frame_ptr[3*pos+0]<=thred_g_b_h
		&& frame_ptr[3*pos+1]>=thred_g_g_l && frame_ptr[3*pos+1]<=thred_g_g_h
		&& frame_ptr[3*pos+2]>=thred_g_r_l && frame_ptr[3*pos+2]<=thred_g_r_h
		&& hsv_ptr[3*pos+0]  >=thred_g_h_l && hsv_ptr[3*pos+0]  <=thred_g_h_h
		&& (hsv_ptr[3*pos+0] <= 10 || hsv_ptr[3*pos+0] >= 30)
		&& hsv_ptr[3*pos+1]  >=thred_g_s_l && hsv_ptr[3*pos+1]  <=thred_g_s_h
		&& hsv_ptr[3*pos+2]  >=thred_g_v_l && hsv_ptr[3*pos+2]  <=thred_g_v_h
		)
		return TRUE;
	else
		return FALSE;
}
bool R(uchar* frame_ptr, uchar* hsv_ptr, int pos)
{
	if(frame_ptr[3*pos+0]    >=thred_r_b_l && frame_ptr[3*pos+0]<=thred_r_b_h
		&& frame_ptr[3*pos+1]>=thred_r_g_l && frame_ptr[3*pos+1]<=thred_r_g_h
		&& frame_ptr[3*pos+2]>=thred_r_r_l && frame_ptr[3*pos+2]<=thred_r_r_h
		&& hsv_ptr[3*pos+0]  >=thred_r_h_l && hsv_ptr[3*pos+0]  <=thred_r_h_h
		&& hsv_ptr[3*pos+1]  >=thred_r_s_l && hsv_ptr[3*pos+1]  <=thred_r_s_h
		&& hsv_ptr[3*pos+2]  >=thred_r_v_l && hsv_ptr[3*pos+2]  <=thred_r_v_h
		)
		return TRUE;
	else
		return FALSE;
}
//1 bgr	2 brg	3 gbr 4 grb	5 rbg 6 rgb
void getloc(IplImage *frame, IplImage* hsv, int bgr)//bgr为要寻找的柱子顺序（从上到下）
{
	uchar* hsv_ptr;
	uchar* frame_ptr;
	uchar* result_ptr;
	int yes[DEC] = {0};
	int num = 0;
	int count = 0;
	int interval = 640/DEC;
	int center = 0;
	int centernum = 0;
	for(num=0;num<DEC;num++)
	{
		for(y=0;y<frame->height;y++)
		{
			frame_ptr = (uchar*)(frame->imageData+y*frame->widthStep);
			hsv_ptr = (uchar*)(hsv->imageData+y*hsv->widthStep);
			for(x=num*interval;x<(num+1)*interval;x++)
			{
				if(B(frame_ptr, hsv_ptr, x))
				{
					b_num++;
					b_y += y;
					
				}
				
				if(G(frame_ptr, hsv_ptr, x))
				{
					g_num++;
					g_y += y;
				}
				
				if(R(frame_ptr, hsv_ptr, x))
				{
					r_num++;
					r_y += y;
				}
			}
		}
		b_y /= b_num;
		g_y /= g_num;
		r_y /= r_num;
		if(b_num>=20 && g_num>=20 && r_num>=20)			//参数！！！！！！！！！！！！！！！！！！！！！！！！
		{
			switch(bgr)
			{
			case 1:{if(b_y<g_y&&g_y<r_y)	ok = 1;break;}	//bgr
			case 2:{if(b_y<r_y&&r_y<g_y)	ok = 1;break;}	//brg
			case 3:{if(g_y<b_y&&b_y<r_y)	ok = 1;break;}	//gbr
			case 4:{if(g_y<r_y&&r_y<b_y)	ok = 1;break;}	//grb
			case 5:{if(r_y<b_y&&b_y<g_y)	ok = 1;break;}	//rbg
			case 6:{if(r_y<g_y&&g_y<b_y)	ok = 1;break;}	//rgb
			}
			if(ok)
			{
				center += (num*interval);
				centernum++;
				yes[num] = 1;
				cvRectangle(frame, cvPoint(num*interval, 0), cvPoint((num+1)*interval, 479), cvScalar(97, 0, 255));
			}
		}
		ok = 0;
		b_num = 0;
		g_num = 0;
		r_num = 0;
		b_y = 0;
		g_y = 0;
		r_y = 0;
	}
//	printf("%d\n", centernum);
	if(centernum == 0)// && start >= 10)
	{
		found = 0;
		on = 0;
		if(flag3 == 0 && foundornot == 1)
		{
			oning ++;
			if(oning>=10 && !oningornot)
			{
				oningornot = 1;
				printf("oning\n");
			}
		}
		notfound++;
		if(notfound>=5 && start >= 10 && widthflag == 1)
		{
			widthflag = 0;
			notfound = 0;
			if(flag1 == 1)
				flag1 = 0;
			else if(flag2 == 1)
				flag2 = 0;
			else if(flag3 == 1)
				flag3 = 0;
			//else if(flag4 == 1)
			//	flag4 = 0;
		}
		else
		{
			sentToUART(0x00, com);
			//printf("0\n");
		}
	}
	if(centernum != 0)
	{
		//oning = 0;
		if(flag3 == 0 && !foundornot)
		{
			found ++;
			if(found >= 20)
			{
				foundornot = 1;
				printf("found\n");
			}
		}
		
		if(oningornot == 1 && flag5 == 1)				//上楼梯与否！！！！！！！！！！！！！！！！！！！！！！！！！！
		{
			//if(centernum >= 24)
			//{
			//	on ++;
			//}
			//else
			//{
			//	on = 0;
			//}
			on ++;
			if(on >= 20)
			{
				printf("on\n");
				oningornot = 0;
				flag5 = 0;
				sentToUART(0xf5, com);
				cvWaitKey(10);
				sentToUART(0xf5, com);
				cvWaitKey(10);
				sentToUART(0xf5, com);
				cvWaitKey(10);
				sentToUART(0xf5, com);
				cvWaitKey(10);
				sentToUART(0xf5, com);
				cvWaitKey(10);
				sentToUART(0xf5, com);
				cvWaitKey(10);
				sentToUART(0xf5, com);
				cvWaitKey(10);
				sentToUART(0xf5, com);
				cvWaitKey(10);
				sentToUART(0xf5, com);
				cvWaitKey(10);
				sentToUART(0xf5, com);
				cvWaitKey(10);
				sentToUART(0xf5, com);
				cvWaitKey(10);
				sentToUART(0xf5, com);
				cvWaitKey(10);
				sentToUART(0xf5, com);
				cvWaitKey(10);
				sentToUART(0xf5, com);
				cvWaitKey(10);
				sentToUART(0xf5, com);
				cvWaitKey(10);
				sentToUART(0xf5, com);
				cvWaitKey(10);
				sentToUART(0xf5, com);
				cvWaitKey(10);
				sentToUART(0xf5, com);
				cvWaitKey(10);
				sentToUART(0xf5, com);
				cvWaitKey(10);
				sentToUART(0xf5, com);
				cvWaitKey(10);
				sentToUART(0xf5, com);
				cvWaitKey(10);
				sentToUART(0xf5, com);
				cvWaitKey(10);
				sentToUART(0xf5, com);
				cvWaitKey(10);
				sentToUART(0xf5, com);
				cvWaitKey(10);
				sentToUART(0xf5, com);
				cvWaitKey(10);
				sentToUART(0xf5, com);
				cvWaitKey(10);
				sentToUART(0xf5, com);
				cvWaitKey(10);
				sentToUART(0xf5, com);
				cvWaitKey(10);
				sentToUART(0xf5, com);
				cvWaitKey(10);
				sentToUART(0xf5, com);
				cvWaitKey(10);
				sentToUART(0xf5, com);
				cvWaitKey(10);
				sentToUART(0xf5, com);
				cvWaitKey(10);
				sentToUART(0xf5, com);
				cvWaitKey(10);
				sentToUART(0xf5, com);
				cvWaitKey(10);
				sentToUART(0xf5, com);
				cvWaitKey(10);
				sentToUART(0xf5, com);
				cvWaitKey(10);
				sentToUART(0xf5, com);
				printf("\t\t5\n");
			}
		}
		if(centernum >= 20)		//参数！！！！！！！！！！！！！！！！！！！！！！！！！！！！
			widthflag = 1;
		start++;
		notfound = 0;
		center /= centernum;
		center += interval/2;
		if(flag1 == 1)
			center = (center-mid1)/50+30;		//3个参数！！！！！！！！！！！！！！！！！！！！！！！！！！
		else if(flag2 == 1)
			center = (center-mid2)/50+30;
		else if(flag3 == 1)
			center = (center-mid3)/50+30;
		else if(flag4 == 1)
			center = (center-mid4)/50+30;
	}
	sentToUART(center, com);
}



int sentToUART(uchar dat, int comnum)
{
	HANDLE hCom;
	unsigned char buf[1];  //要传输串口数据缓冲区
	char com[5] = {"COM"};
	com[4] = '\0';
	switch(comnum)
	{
	case 1:{com[3] = '1';break;}
	case 2:{com[3] = '2';break;}
	case 3:{com[3] = '3';break;}
	case 4:{com[3] = '4';break;}
	case 5:{com[3] = '5';break;}
	case 6:{com[3] = '6';break;}
	case 7:{com[3] = '7';break;}
	case 8:{com[3] = '8';break;}
	case 9:{com[3] = '9';break;}
	}

	//把串口作为文件打开

	hCom=CreateFile( com, //L"COM6", //com6口

		GENERIC_READ|GENERIC_WRITE, //读\写

		0,
		NULL,
		OPEN_EXISTING,  //已存在文件[只能这个]
		0,
		NULL
	);

	if (hCom==(HANDLE)-1)//打开串口失败返回
	{
		
		return 0;
	}

	COMMTIMEOUTS TimeOuts;  //串口超时结构体设置

	TimeOuts.ReadIntervalTimeout=1000;       //填充TimeOuts
	TimeOuts.ReadTotalTimeoutMultiplier=500;
	TimeOuts.ReadTotalTimeoutConstant=5000;
	TimeOuts.WriteTotalTimeoutMultiplier=500;
	TimeOuts.WriteTotalTimeoutConstant=2000;

	if(!SetCommTimeouts(hCom,&TimeOuts))  //与串口绑定 失败返回
		return 0;

	DCB dcb;
	if(!GetCommState(hCom,&dcb)) //获取当前DCB
		return 0;
	dcb.BaudRate = CBR_9600;   //波特率设置19200
	dcb.ByteSize = 8;           //数据位8位

	dcb.Parity = NOPARITY;
	dcb.StopBits = ONESTOPBIT;  //1个停止位

	dcb.fBinary=1;
	dcb.fParity=0;

	if (!SetCommState(hCom, &dcb))  //DCB绑定失败返回
		return 0;

	if (!SetupComm(hCom,1024,1024))//设置串口读写缓冲区[1024]byte 失败返回
	{
		return 0;
	}

	PurgeComm(hCom, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR);
	DWORD ComWriteReturn;

	buf[0] = dat;
	WriteFile(hCom, &buf, 1, &ComWriteReturn, NULL);
	//printf("hi\n");
	CloseHandle(hCom);
}

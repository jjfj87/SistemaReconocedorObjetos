/*
 * PROYECTO: 01 - Colores_video
 * OBJETIVO: Muestra en una ventana el video original que se esta 
 * 			obteniendo de la camara y muestra en otras dos ventanas 
 * 			aparte el mismo video aplicando escala de grises y HSV
 */
 
#include "/home/pi/opencv-3.0.0/include/opencv/highgui.h"
#include "/home/pi/opencv-3.0.0/include/opencv/cv.h"
#include<iostream>

using namespace std;

int main(){
	// Definimos las ventanas
	cvNamedWindow("Original", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("GRAY", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("HSV", CV_WINDOW_AUTOSIZE);
	
	// Especificamos la camara
	CvCapture* capture = cvCreateCameraCapture(0);
	
	IplImage* frame;
	IplImage* frameGray;
	IplImage* frameHSV;
		
	while(1){
		// Se obtiene un frame de la camara
		frame = cvQueryFrame(capture);
		
		// Se comprueba si ha habido error
		if(!frame){
			cout << "ERROR: No se detecta el frame" << endl;
			break;
		}
		
		// Se define el tamaño del frame
		CvSize tamano_frame = cvSize(frame->width, frame->height);

		// Se crea la imagen en escala de grises. Primero se especifica 
		// el numero de bits y el de canales y luego se transforma de 
		// RGB a GRAY
		frameGray = cvCreateImage(tamano_frame, IPL_DEPTH_8U, 1);
		cvCvtColor(frame, frameGray, CV_BGR2GRAY);
		
		// Se crea la imagen en escala de grises. Primero se especifica 
		// el numero de bits y el de canales y luego se transforma de 
		// RGB a HSV
		frameHSV = cvCreateImage(tamano_frame, IPL_DEPTH_8U, 3);
		cvCvtColor(frame, frameHSV, CV_BGR2HSV);
		
		// Se muestran las imagenes en cada pantalla
		cvShowImage("Original", frame);
		cvShowImage("GRAY", frameGray);
		cvShowImage("HSV", frameHSV);

		// Se espera una tecla
		char c = cvWaitKey(10);
		
		// Si la tecla es ESC, ...
		if(c == 27)	
			// ... se sale del bucle
			break;
	}
	
	// Se libera la camara
	cvReleaseCapture(&capture);
	
	// Se destruyen las ventanas creadas
	cvDestroyWindow("Original");
	cvDestroyWindow("GRAY");
	cvDestroyWindow("HSV");

	return 0;
}

/*
 * PROYECTO: 02 - ROI_video
 * OBJETIVO: Muestra en una ventana el frame original que se ha obtenido 
 * 			de la camara y muestra en otra ventana la region ROI especificada.
 */
 
#include "/home/pi/opencv-3.0.0/include/opencv/highgui.h"
#include "/home/pi/opencv-3.0.0/include/opencv/cv.h"
#include<iostream>

using namespace std;

int main(){
	// Definimos las ventanas
	cvNamedWindow("Original", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("ROI", CV_WINDOW_AUTOSIZE);
	
	// Especificamos la camara
	CvCapture* capture = cvCreateCameraCapture(0);
	
	IplImage* frame;
	IplImage* frameROI;
	
	// Se crean los puntos inicial y final de la region ROI
	CvPoint ini, fin;
	
	ini.x = 50;
	ini.y = 50;
	
	fin.x = 350;
	fin.y = 350;
	
	// Se obtiene un frame de la camara
	frame = cvQueryFrame(capture);
	
	// Se comprueba si ha habido error
	if(!frame){
		cout << "ERROR: No se detecta el frame" << endl;
	}
		
	// Se obtiene el tamaño de la region ROI
	int ancho = fin.x - ini.x;
	int alto = fin.y - ini.y;
	
	// Se clona la imagen original en la que se obtendra la region ROI
	frameROI = cvCloneImage(frame);
	
	// Seleccionamos la region ROI. Ahora se pierde lo que habia en 
	// frameROI y se guarda en ella la region ROI
	cvSetImageROI(frameROI, cvRect(ini.x, ini.y, ancho, alto));
				
	// Se muestran las imagenes en cada pantalla
	cvShowImage("Original", frame);
	cvShowImage("ROI", frameROI);
	
	// Se espera a que se pulse una tecla
	cvWaitKey(0);
	
	// Se libera la camara
	cvReleaseCapture(&capture);
	
	// Se destruyen las ventanas creadas
	cvDestroyWindow("Original");
	cvDestroyWindow("ROI");

	return 0;
}

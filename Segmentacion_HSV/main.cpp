/*
 * PROYECTO: 07 - Segmentacion HSV
 * OBJETIVO: Muestra en una ventana el frame original y en otra la 
 * 			imagen segmentada en base al color especificado en la funcion
 * 			GetThresholdedImage. En este caso se detecta el color AZUL.
 */
 
#include "/home/pi/opencv-3.0.0/include/opencv/highgui.h"
#include "/home/pi/opencv-3.0.0/include/opencv/cv.h"
#include<iostream>

using namespace std;

// Funcion segmentar
IplImage* GetThresholdedImage(IplImage* frame){
	// Se convierte el frame original en modelo RGB a HSV
	IplImage* frameHSV = cvCreateImage(cvGetSize(frame), 8, 3);
	cvCvtColor(frame, frameHSV, CV_BGR2HSV);
	
	// Se crea una nueva imagen con 1 canal 
	IplImage* frameSEG = cvCreateImage(cvGetSize(frame), 8, 1);
	
	// Se realiza la segmentacion de los pixeles que esten comprendidos
	// entre los valores especificados, en este caso, entre (115,0,0)
	// y (150,255,255). Se detecta el color azul (para saber el codigo
	// del color se ha usado el programa de obtener el codigo de un color)
	cvInRangeS(frameHSV, cvScalar(115, 0, 0), cvScalar(150, 255, 255), frameSEG);
	
	// Se libera la imagen
	cvReleaseImage(&frameHSV);
	
	return frameSEG;
}

int main(){
	// Definimos las ventanas
	cvNamedWindow("Original", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("Segmentada", CV_WINDOW_AUTOSIZE);
	
	// Especificamos la camara
	CvCapture* capture = cvCreateCameraCapture(0);
	
	IplImage* frame;
	IplImage* frameSEG;
	
	// Se obtiene un frame de la camara
	frame = cvQueryFrame(capture);
	
	// Se comprueba si ha habido error
	if(!frame){
		cout << "ERROR: No se detecta el frame" << endl;
	}
	
	// Se segmenta la imagen
	frameSEG = GetThresholdedImage(frame);
	
	// Se muestra la imagen
	cvShowImage("Original", frame);
	cvShowImage("Segmentada", frameSEG);
	
	// Se espera a que se pulse una tecla
	cvWaitKey(0);
	
	// Se libera la camara
	cvReleaseCapture(&capture);
	
	// Se liberan las imagenes
	cvReleaseImage(&frame);
	cvReleaseImage(&frameSEG);
	
	// Se destruyen las ventana creada
	cvDestroyAllWindows();

	return 0;
}

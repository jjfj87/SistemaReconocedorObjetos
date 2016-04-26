/*
 * PROYECTO: 03 - CambiarTamanioImagen
 * OBJETIVO: Muestra en una ventana el frame original que se ha obtenido 
 * 			de la camara y muestra en otra el frame con otro tamano
 */
 
#include "/home/pi/opencv-3.0.0/include/opencv/highgui.h"
#include "/home/pi/opencv-3.0.0/include/opencv/cv.h"
#include<iostream>

using namespace std;

int main(){
	// Definimos las ventanas
	cvNamedWindow("Original", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("Modificado", CV_WINDOW_AUTOSIZE);
	
	// Especificamos la camara
	CvCapture* capture = cvCreateCameraCapture(0);
	
	IplImage* frame;
	IplImage* frameModificado;
	
	// Se obtiene un frame de la camara
	frame = cvQueryFrame(capture);
	
	// Se comprueba si ha habido error
	if(!frame){
		cout << "ERROR: No se detecta el frame" << endl;
	}
	
	// Se especifica el tamano del frame modificado
	frameModificado = cvCreateImage(cvSize(300, 300), IPL_DEPTH_8U, 3);
	
	// Se reescala la image
	cvResize(frame, frameModificado, CV_INTER_CUBIC);
				
	// Se muestran las imagenes en cada pantalla
	cvShowImage("Original", frame);
	cvShowImage("Modificado", frameModificado);
	
	// Se espera a que se pulse una tecla
	cvWaitKey(0);
	
	// Se libera la camara
	cvReleaseCapture(&capture);
	
	// Se destruyen las ventanas creadas
	cvDestroyWindow("Original");
	cvDestroyWindow("Modificado");

	return 0;
}

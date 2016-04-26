/*
 * PROYECTO: 05 - Segmentacion (CREO QUE NO FUNCIONA DEL TODO)
 * OBJETIVO: Muestra en una ventana el frame original que se ha obtenido 
 * 			de la camara y en otra el frame segmentado con respecto al  
 * 			color especificado.
 */
 
#include "/home/pi/opencv-3.0.0/include/opencv/highgui.h"
#include "/home/pi/opencv-3.0.0/include/opencv/cv.h"
#include<iostream>

using namespace std;

IplImage* segmentacion_RGB(IplImage* frame){
	// Declaracion de variables necesarias
	int alto, ancho, ancho_fila, canales;
	uchar *data;
	int i, j;
	
	// Recopilacion de los datos de la imagen original
	alto = frame->height;
	ancho = frame->width;
	ancho_fila = frame->widthStep;
	canales = frame->nChannels;
	data = (uchar *)frame->imageData;
	
	// Se inicializa a '0' la imagen modificada y se especifica 1 canal
	// porque va a ser una imagen binaria (0 o 1, negro o blanco)
	IplImage* frameModificado;
	frameModificado = cvCreateImage(cvGetSize(frame), IPL_DEPTH_8U, 1);
	cvZero(frameModificado);
	
	// Recorrido de la imagen original
	for(i = 0; i < alto; i++){
		for(j = 0; j < ancho; j++){
			// Seleccion de tonalidades rojas
			if((data[i*ancho_fila + j*canales + 2] > 80) &&
			  !((data[i*ancho_fila + j*canales + 0] > data[i*ancho_fila + j*canales + 2]/2) ||
			  (data[i*ancho_fila + j*canales + 1] > data[i*ancho_fila + j*canales + 2]/2))){
				  // Activacion de los pixeles que cumplen la condicion de color fijada
				  frameModificado->imageData[frameModificado->widthStep * i + j*1] = 1;
			  }
		}
	}
	
	// EROSION para la eliminacion de pixeles sueltos
	cvErode(frameModificado, frameModificado, NULL, 1);
	
	// DILATACION para expandir los objetos de la imagen
	cvDilate(frameModificado, frameModificado, NULL, 3);
	
	return frameModificado;
}

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
	
	// Se realiza la segmentacion del frame original en base al color ROJO
	frameModificado = segmentacion_RGB(frame);
	
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

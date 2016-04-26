/*
 * PROYECTO: 04 - EscribirEnImagen
 * OBJETIVO: Muestra en una ventana el frame original que se ha obtenido 
 * 			de la camara y en otra el frame con un texto escrito en la 
 * 			posicion especificada.
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
	
	// Se clona el frame original en el modificado
	frameModificado = cvCloneImage(frame);
	
	// Se define la fuente del texto
	CvFont fuente;
	// cvInitFont(variable, tipo_letra, escala_horizontal, escala_vertical, shear, grosor(opc), tipo_linea(opc))
	cvInitFont(&fuente, CV_FONT_VECTOR0, 0.5, 0.5, 0);
	
	// Se define el punto donde se situara el texto y se pone el texto
	CvPoint pto = cvPoint(100, 100);	 //pto.x = 100; 	pto.y = 100;
	cvPutText(frameModificado, "Hola", pto, &fuente, CV_RGB(255, 190,44));
	
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

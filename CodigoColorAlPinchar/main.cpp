/*
 * PROYECTO: 06 - CodigoColorAlPinchar
 * OBJETIVO: Muestra en una ventana el frame original y al pulsar con el
 * 			raton aparece una nueva ventana con una etiqueta con los 
 * 			colores RGB del pixel.
 */
 
#include "/home/pi/opencv-3.0.0/include/opencv/highgui.h"
#include "/home/pi/opencv-3.0.0/include/opencv/cv.h"
#include<iostream>

using namespace std;

// Se va ejecutando todo el tiempo con cualquier evento del raton
void mouseHandler(int event, int x, int y, int flags, void* param){
	// Declaracion de variables
	IplImage* img;
	CvFont fuente;
	uchar *ptr;
	char label[20];
	
	// Se pasa la imagen(param) que tiene tipo (void*) a tipo (IplImage*)
	img = (IplImage*) param;
	
	// Se inicializa la fuente
	// cvInitFont(variable, tipo_letra, escala_horizontal, escala_vertical, shear, grosor(opc), tipo_linea(opc))
	cvInitFont(&fuente, CV_FONT_HERSHEY_PLAIN, 0.8, 0.8, 0, 1, 8);
		
	// Si el evento es "clic izquierdo", ...
	if(event == CV_EVENT_LBUTTONDOWN){
		// Se realiza la lectura del pixel pulsado
		ptr = cvPtr2D(img, y, x, NULL);
		
		// Se muestra el valor RGB
		sprintf(label, "(%d, %d, %d)", ptr[0], ptr[1], ptr[2]);
		
		// Se crea un rectangulo de color en la imagen
		cvRectangle(img, cvPoint(x, y-12), cvPoint(x+100, y+4), CV_RGB(255, 0, 0), CV_FILLED, 8, 0);
		
		// Se pone el texto en su interior
		cvPutText(img, label, cvPoint(x, y), &fuente, CV_RGB(255, 255, 0));
		
		// Se muestra la imagen
		cvShowImage("Ventana con codigo", img);
	}
}

int main(){
	// Definimos las ventanas
	cvNamedWindow("Ventana", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("Ventana con codigo", CV_WINDOW_AUTOSIZE);
	
	// Especificamos la camara
	CvCapture* capture = cvCreateCameraCapture(0);
	
	IplImage* frame;
	IplImage* frameHSV;
	
	// Se obtiene un frame de la camara
	frame = cvQueryFrame(capture);
	
	// Se comprueba si ha habido error
	if(!frame){
		cout << "ERROR: No se detecta el frame" << endl;
	}
	
	// Se clona el frame original en la otra variable para despues 
	// realizar filtros sobre ella
	frameHSV = cvCloneImage(frame);
	
	// Se transforma de modelo RGB a modelo HSV
	cvCvtColor(frame, frameHSV, CV_BGR2HSV);
	
	// Se añaden los eventos del ratón a la ventana creada
	cvSetMouseCallback("Ventana", mouseHandler, (void*)frameHSV);
	
	// Se muestra la imagen
	cvShowImage("Ventana", frameHSV);
	
	// Se espera a que se pulse una tecla
	cvWaitKey(0);
	
	// Se libera la camara
	cvReleaseCapture(&capture);
	
	// Se liberan las imagenes
	cvReleaseImage(&frame);
	cvReleaseImage(&frameHSV);
	
	// Se destruyen las ventana creada
	cvDestroyAllWindows();

	return 0;
}

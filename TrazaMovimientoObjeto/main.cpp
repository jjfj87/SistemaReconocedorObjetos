/*
 * PROYECTO: 08 - TrazaMovimientoObjeto
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
	
	// Se comprueba si ha habido error
	if(!capture){
		cout << "ERROR: No se detecta la camara" << endl;
	}
	
	IplImage* imgScribble = NULL;
	
	while(true){
		IplImage* frame = 0;
		
		// Se obtiene un frame de la camara
		frame = cvQueryFrame(capture);
		
		// Si no se ha obtenido la imagen, mostramos error
		if(!frame){
			cout << "ERROR: No se detecta el frame" << endl;
			break;
		}
		
		// Asignamos memoria para la imagen
		if(imgScribble == NULL){
			imgScribble = cvCreateImage(cvGetSize(frame), 8, 3);
		}
		
		// Se segmenta la imagen
		IplImage* imgBlueThresh = GetThresholdedImage(frame);
		
		// Se reserva espacio en memoria para la estructura de momentos
		CvMoments* moments = (CvMoments*) malloc(sizeof(CvMoments));
		
		cvMoments(imgBlueThresh, moments, 1);
		
		// Se obtiene el momento inicial y el final
		double moment10 = cvGetSpatialMoment(moments, 1, 0);
		double moment01 = cvGetSpatialMoment(moments, 0, 1);
		
		double area = cvGetCentralMoment(moments, 0, 0);
		
		// Se almacena la posicion actual del objeto
		static int posX = 0;
		static int posY = 0;
		
		// Se almacena el ultimo momento del objeto
		int lastX = posX;
		int lastY = posY;
		
		// Se obtienen las coordenadas dividiendo por el area
		posX = moment10 / area;
		posY = moment01 / area;
		
		// Se imprime la posicion del objeto
		cout << "posicion: (" << posX << ", " << posY << ")" << endl;
		
		// Si es una posicion valida...
		if(lastX > 0 && lastY > 0 && posX > 0 && posY > 0){
			// ... pintamos una linea amarilla con un ancho de 5 pixeles
			cvLine(imgScribble, cvPoint(posX, posY), cvPoint(lastX, lastY), cvScalar(0,255,255), 5);
		}
		
		// Se combina la traza con la imagen
		cvAdd(frame, imgScribble, frame);
		
		// Se muestra la imagen
		cvShowImage("Original", frame);
		cvShowImage("Segmentada", imgBlueThresh);
		
		// Se espera una tecla
		char c = cvWaitKey(10);
		
		// Si se pulsa ESC, ...
		if(c == 27)	
			// ... se sale del bucle
			break;
			
		// Se libera la imagen y la estructura
		cvReleaseImage(&imgBlueThresh);
		delete moments;
	}
	
	// Se libera la camara
	cvReleaseCapture(&capture);
	
	// Se destruyen las ventana creada
	cvDestroyAllWindows();

	return 0;
}

//videojuego    ganar perder vida monedas
#include <iostream>
#include <fstream>
#include <ctime>
#include <stdlib.h>
#include <locale.h>

using namespace std;

int inicio();
//funciones modo historia
void nuevaPartida_h(), cargarPartida_h(), guardarPartida_h(), menuNivel(); //acciones usuario  
void pelea(), pelea_final(), muerte(), endgame(), presionar_continuar(); //acciones usuario durante el juego
void datos_Partida(), mapa(), reptiliano_1(), reptiliano_2(), dio(); //recursos visuales
void parte_Nivel(), nivel_1(), nivel_2(), nivel_3(), nivel_4(), nivel_5(); //niveles

string  s_hp, s_oro, s_dpa, s_lvl;
int continuar_1, continuar_pelea, aleatorio;
int ataque_jefe = 5, vida_jefe = 25;
int hp, oro, dpa, lvl;
//funciones modo DIO
void nuevaPartida_d(), cargarPartida_d(), guardarPartida_d(), menu_dio(), resultado_Datos();

int main(){//==========================================================================================
	setlocale(LC_CTYPE, "Spanish");	
		inicio();
}

int inicio(){ //Menu del inicio del juego
	int teclaEmpezar;
	cout<<"  ===================================================================================="<<endl;
	cout<<"                               BIENVENIDO A COLOMBUS 127                              "<<endl;
	cout<<"  ===================================================================================="<<endl;
	cout<<"                     Por favor, ingrese la acci�n que desea realizar,                 "<<endl;
    cout<<"\n  MODO HISTORIA\n  1 Crear nueva partida\n  2 Cargar partida guardada\n\n  MODO DIO"<<endl;
    cout<<"  3 Crear nueva partida\n  4 Cargar partida guardada\n\n  Modo historia: empr�ndete en una incre�ble";
    cout<<" historia por el espacio en busca de\n  aventuras luchando contra enemigos desconocidos"<<endl;
    cout<<"\n  Modo DIO: Convi�rtete en una deidad controlando a un personaje aumentando o \n  disminuyendo";
    cout<<" sus estad�sticas a tu antojo (vida, monedas y da�o)\n\n"<<endl;
    cout<<"                                           ";
		cin>>teclaEmpezar;
		if(teclaEmpezar == 1){
			nuevaPartida_h();
			datos_Partida();//depues de crear nueva partida muestra al usuario sus estadisticas
		}else if(teclaEmpezar == 2){
			cargarPartida_h();
			datos_Partida();//al cargar partida le muestra sus estadisticas 
		}else if(teclaEmpezar == 3){
			nuevaPartida_d();
				system("cls"); //limpiar el menu
			resultado_Datos();	//iniciando un partida te muestra tus nuevas estadiscticas
		}else{
			cargarPartida_d();
				system("cls");
			resultado_Datos(); //muestra tus estadisticas guardadas
		}
}
/////////////////////////////					MODO HISTORIA					/////////////////////////////

void nuevaPartida_h(){ //El usuario decide crear una nueva partida
	ofstream archivoPP;
	archivoPP.open("DatosPerP-ModoHistoria.txt",ios::out);//abrir archivo para datos del personaje principal
	
	if(!archivoPP.fail()){
		archivoPP<<"hp:100."<<endl;//vida
		archivoPP<<"or:0."<<endl; //monedas
		archivoPP<<"dpa:10."<<endl; //da�o por ataque 
		archivoPP<<"lv:1."<<endl; //nivel (1 de 5)
	}else{//no se encuentra ARCHIVO
		cout<<"Imposible realizar esta operacion";
		exit(1);
	}
	cargarPartida_h();//carga los datos del archivo recientemente creado
}


void cargarPartida_h(){ //El usurio carga una parida ya guardada
	ifstream archivoPP;
	string datos;
	bool hp_flag = false, oro_flag = false, dpa_flag = false, lvl_flag = false;
	
	archivoPP.open("DatosPerP-ModoHistoria.txt",ios::in);//abre el archivo
		if(!archivoPP.fail()){
			while(!archivoPP.eof()){
			getline(archivoPP,datos);
				for(int i = 0; i < datos.size(); i++){
					switch(datos[i]){
						case 'h': //busca en el archivo a hp (vida)
							for(int i = 0; i < datos.size(); i++){
								if(datos[i] == ':'){
									hp_flag = true;//encuentra el :
								}else{
									if(hp_flag == true){
										if(datos[i] != '.'){//guardar todo siempre que no sea un .
											s_hp = s_hp + datos[i]; //guarda el puntaje
										}
									}
								}
							}break;
						case 'o': //buscar en archivo or (oro)
							for(int i = 0; i < datos.size(); i++){
								if(datos[i] == ':'){
									oro_flag = true;//encuentra el :
								}else{
									if(oro_flag == true){
										if(datos[i] != '.'){//guardar todo siempre que no sea un .
											s_oro = s_oro + datos[i];//guardar puntaje
										}
									}
								}
							}break;
						case 'd': //buscar en archivo dpa (da�o por ataque)
							for(int i = 0; i < datos.size(); i++){
								if(datos[i] == ':'){
									dpa_flag = true;//cuando encuentra el:
								}else{
									if(dpa_flag == true){
										if(datos[i] != '.'){//guardar todo siempre que no sea un .
											s_dpa = s_dpa + datos[i];//guardar puntaje
										}
									}
								}
							}break;
						case 'l': //buscar en archivo lv (nivel)
							for(int i = 0; i < datos.size(); i++){
								if(datos[i] == ' 	:'){
									lvl_flag = true;//cuando encuentre el :
								}else{
									if(lvl_flag == true){
										if(datos[i] != '.'){//guardar todo siempre que no sea un .
											s_lvl = s_lvl + datos[i];//guardar puntaje
										}
									}
								}
							}break;
					}
				}
			}
		}else{//el archivo no pudo ser leido
			cout<<"Imposible realizar esta operaci�n";
			exit (2);
		}
	hp = atoi(s_hp.c_str());//convertir los datos a enteros
	oro = atoi(s_oro.c_str());
	dpa = atoi(s_dpa.c_str());
	lvl = atoi(s_lvl.c_str());
	s_hp.erase(); s_oro.erase(); s_dpa.erase(); s_lvl.erase();//borrar valor de variables string
}


void guardarPartida_h(){//funcion para guardar partida
	ofstream archivoPP;
	archivoPP.open("DatosPerP-ModoHistoria.txt",ios::out);//abrir archivo para datos del personaje principal
	
	if(!archivoPP.fail()){
		archivoPP<<"hp:"<<hp<<"."<<endl;//vida
		archivoPP<<"or:"<<oro<<"."<<endl; //monedas
		archivoPP<<"dpa:"<<dpa<<"."<<endl; //da�o por ataque 
		archivoPP<<"lv:"<<lvl<<"."<<endl; //nivel (1 de 5)
	}else{
		cout<<"Imposible realizar esta operacion";//no se encontro el archivo para guardar
		exit(1);
	}
}


void parte_Nivel(){//llevara al usuario a la parte del nivel que tenga su variable lvl
	if (lvl == 1){
		nivel_1();
	}else if (lvl == 2){
		nivel_2();		
	}else if (lvl == 3){
		nivel_3();		
	}else if (lvl == 4){	
		nivel_4();		
	}else if (lvl == 5){
		nivel_5();	
	}
}


void nivel_1(){//PRIMER NIVEL
	system("cls");
		cout<<"  ===================================================================================="<<endl;
		cout<<"                               BIENVENIDO A COLOMBUS 127                              "<<endl;
	presionar_continuar();
		cout<<"                              El fin justifica los medios.                         "<<endl;
		cout<<"                                 - Nicol�s Maquiavelo -                            "<<endl;
		cout<<"  ===================================================================================="<<endl;
		cout<<"  Te has despertado en un lugar extra�o, tienes jaqueca y mareos. Intentas abrir los  "<<endl;
		cout<<"  ojos pero no logras ver nada, primero oscuridad, despu�s luz. Todo es tu culpa"    <<endl;
	presionar_continuar();
		cout<<"  Comienzas a distinguir figuras, la luz deja de ser luz y se convierte en color, no "<<endl;
		cout<<"  tienes ni idea de donde estas. Observas a tu alrededor, te encuentras dentro de una"<<endl;
		cout<<"  clase de tubo, pero esta destruido permiti�ndote el paso. Ves sangre, tienes miedo a"<<endl;
		cout<<"  salir, pero no te queda de otra. Una figura flotante se encuentra en penumbra y  "<<endl;
		cout<<"  acech�ndote, decides salir, la figura se acerca, te cortas el brazo con los vidrios "<<endl;
		cout<<"  del tubo, la figura saca chispas de su cuerpo. Est�n frente a frente.       "<<endl<<endl;
		cout<<"                  Si tan solo tuviera m�s tiempo lo hubiera aprovechado               "<<endl;
	presionar_continuar();
		cout<<"  Frente a m� se encontraba un robot peque�o, pero al volar ten�a poco menos de mi"<<endl;
		cout<<"  altura. En su pantalla pod�a ver lo que quer�a decirme, pero la �nica forma en la"<<endl;
		cout<<"  cual yo pod�a interactuar con �l era por su pantalla donde formaba un teclado"<<endl;
		cout<<"  en el cual pod�a escribir todo lo que necesitara"<<endl;
	presionar_continuar();
		cout<<"                                                                                      "<<endl;
		cout<<"                                *                                                     "<<endl;
		cout<<"                                *                                                     "<<endl;
		cout<<"                                *                                                     "<<endl;
		cout<<"                                *                                                     "<<endl;
		cout<<"                            *********************************                         "<<endl;
		cout<<"                            *                               *                         "<<endl;
		cout<<"                            *         HOLA USUARIO          *                         "<<endl;
		cout<<"                            *                               *                         "<<endl;
		cout<<"                            *          X         X          *                         "<<endl;
		cout<<"                            *         X X       X X         *                         "<<endl;
		cout<<"                            *          X         X          *                         "<<endl;
		cout<<"                            *     X                   X     *                         "<<endl;
		cout<<"                            *      XXXXXXXXXXXXXXXXXXX      *                         "<<endl;
		cout<<"                            *                               *                         "<<endl;
		cout<<"                            *********************************                         "<<endl;
		cout<<"                            *  o o o              Throper 7 *                         "<<endl;
		cout<<"                            *********************************                         "<<endl;
		cout<<"                                *                     *                               "<<endl;
		cout<<"                                *                     *                               "<<endl;
		cout<<"                                *                     *                               "<<endl;
		cout<<"                              *****                                                   "<<endl;
		cout<<"                              *   *                                                   "<<endl;
	presionar_continuar();
		cout<<"  Robot en pantalla - Hola, usuario, felicidades, la criogenizaci�n ha terminado,     "<<endl;
		cout<<"                      estas listo para servir a tu raza en busca de nuevas aventuras y"<<endl;
		cout<<"                      conocimientos para los humanos. �Quisieras tomar el curso        "<<endl;
		cout<<"                      introductorio?\n  Presiona 1 si es as�, de no ser as�, presiona 2  "<<endl;
		cout<<"  ===================================================================================="<<endl;
		cout<<"                                           ";
		cin>>continuar_1;
			while(continuar_1 != 1){ // mientras el usuario no digite 1 seguir� mostrando el mismo texto
					cout<<"  ======================================================================================="<<endl;
					cout<<"  �Quisieras tomar el curso introductorio? Presiona 1 si es as�, de no ser as�, presiona 2"<<endl;
					cout<<"  ======================================================================================="<<endl;
						cout<<"                                           ";
				cin>>continuar_1;
			}
						continuar_1 = 10; //se cambia el valor de la variable anteriormente usada
	system("cls");
		cout<<"  ===================================================================================="<<endl;
		cout<<"  Robot en pantalla - Excelente =)  Ha decidido tomar el curso intro..."<<endl;
		cout<<endl;
		cout<<"  El robot parece que se ha trabado, que deber�a hacer?\n  1 Golpear\n  2 Hablarle bonito"<<endl;
		cout<<"  ";cin>>continuar_1;
		while(continuar_1 != 1){		//nuevamente se hace un bucle esperando una respuesta especifica
			cout<<"  Es un robot NO POSEE EMOCIONES. Intente de nuevo"<<endl;
			cout<<"  ";cin>>continuar_1;
		}
	system("cls");
		cout<<"  ===================================================================================="<<endl;
		cout<<"  El robot se apaga, se mantiene un rato apagado. Decides examinar la habitaci�n, es  "<<endl;
		cout<<"  bastante grande, observas a lo lejos el tubo que te conten�a, la sangre de tu brazo "<<endl;
		cout<<"  brillante que se qued� en el cristal, pero no es la �nica sangre en la habitaci�n, "<<endl;
		cout<<"  puedes ver manchas, charcos de sangre, una buena parte de la habitaci�n esta"<<endl;
		cout<<"  destruida, te preguntas si la sangre ser� tuya cuando el robot vuelve a iniciar   "<<endl;
	presionar_continuar();
		cout<<"  Robot en pantalla - ..."<<endl;
		cout<<"\n  Programa Throper 7.17.1 inicializando...\n  Comprobaci�n de componentes fallida"<<endl;
		cout<<"  Realizando an�lisis de manera profunda...10%\n  Error...Datos err�neos...Error (119)\n  Reestableciendo sistema...";
		cout<<"\n  Desea activar la base de datos anteriormente preestablecida?"<<endl;
		cout<<"  ===================================================================================="<<endl;
		cout<<"                              Presione 1 si es asi: ";
		do{
			cin>>continuar_1;
		}while(continuar_1 != 1);
				continuar_1 = 10;
	system("cls");
		cout<<"  ===================================================================================="<<endl;
		cout<<"  Robot en pantalla - ..."<<endl;
		cout<<"  Robot en pantalla - Felicidades, ha logrado reestablecer su unidad Throper 7        "<<endl;
		cout<<"                      inicializando en 3...2...1..."<<endl;
	presionar_continuar();
		cout<<"  Robot en pantalla - �Qui�n eres?"<<endl;
		cout<<"  1 �Qu� te importa? Quiero saber que es este lugar\n  2 Hola, mucho gusto, me llamo Juan Antonio"<<endl;
		cout<<endl<<"  Parece que el Throper 7 al reiniciar su sistema perdi� toda informaci�n almacenada"<<endl;
		cout<<"  menos su programaci�n, ahora no me permite escribir, solamente elegir opciones que "<<endl;
		cout<<"  �l me da, aunque son un poco extra�as, debieron ser demasiado flojos los programadores"<<endl;
		cout<<"                                           ";
		cin>>continuar_1; //el usuario puede elegir dos respuestas, acorde a cada respuesta se le dara informacion distinta
		do{
			while(continuar_1 == 1){ //opcion 1
				cout<<"  Robot en pantalla - ..."<<endl;
				cout<<"                     Buscar� en la base de datos que lugar es este... Grosero :c"<<endl;
				continuar_1 = 10; //cambiar valor para salir 
			}
			while(continuar_1 != 1 && continuar_1 != 10){ //opcion 2
				cout<<"  Robot en pantalla - Hola Juan Antonio, me llamo... no s� c�mo me llamo, debo buscar"<<endl;
				cout<<"                      en la base de datos... Me llamo Throper 7... este lugar es..."<<endl;
				cout<<"                      extra�o... seamos amigos y te dir� d�nde estamos"<<endl;
				continuar_1 = 10;//cambiar valor para salir
			}
		}while(continuar_1 != 10); //la opcion elegida no influye en el juego, influye en la experiencia
	presionar_continuar();
		cout<<"  Dentro de los archivos de mi programaci�n pude encontrar que nos encontramos en una "<<endl;
		cout<<"  nave llamada 'LA FLECHA' porque tiene forma de flecha... que original, debieron haber"<<endl;
		cout<<"  pensado demasiado ese nombre, que ingeniosos. Dime quisieras que te muestre el mapa "<<endl;
		cout<<"  de la nave? \n  1 Si\n  2 No"<<endl;
		cout<<"  ";	cin>>continuar_1;

		while(continuar_1 != 1){//se espera un si de respuesta
		cout<<"  Parece que usted es algo tonto, m�s de lo normal, y ha decidido ignorar completamente"<<endl;
		cout<<"  mi amable advertencia, as� que le preguntare otra vez..."<<endl;
		cout<<"  QUISIERA QUE LE MUESTRE EL MAPA DE LA BENDITA FLECHA?\n  1 Si\n  2 No"<<endl;
		cout<<"  ";	cin>>continuar_1;
		}
	system("cls");
		cout<<"  ===================================================================================="<<endl;
		cout<<"  Parece que has tomado una buena decisi�n, buscare en la base de datos el mapa"<<endl;
		cout<<"  Buscando..."<<endl;
	presionar_continuar();
		cout<<"  He encontrado el mapa..."<<endl;
	mapa();//mostrar el mapa de la nave
	presionar_continuar();
		cout<<"  Parece que nos encontramos en las Habitaciones, no te parece interesante la nota \n  final?";
		cout<<"  Por qu� deber�an permanecer juntos? Tal vez para no perderse... Espero..."<<endl;
	mapa();//mostrar mapa de la nave
	presionar_continuar();
		cout<<"  Robot - Parece que debemos movernos, mis sensores no detectan alg�n movimiento de la"<<endl;
		cout<<"          nave. No es que sea muy listo pero estas manchas de sangre no son tuyas, y"<<endl;
		cout<<"          seg�n los registros que tengo de la nave eran 7 pasajeros humanos, incluy�ndote"<<endl;
		cout<<"          parece que lo que sea que haya matado a los pasajeros tambi�n destruyo parte"<<endl;
		cout<<"          de la nave, debemos movernos a el Puerto de control y ver si podemos poner esto"<<endl;
		cout<<"          a andar, pero te recomiendo que tomes uno de los trajes y un arma..."<<endl;
		cout<<endl<<"  1 Como sabes que les paso a los dem�s pasajeros? Crea que hab�as perdido casi"<<endl;
		cout<<"  todos tus datos guardados?\n\n  2 Vamos, tomare el traje amarillo, combina con mi hor�scopo"<<endl;
		cout<<"                                           ";
		cin>>continuar_1;
		do{//se le da opcion al usuario de escoger su respuesta, no afecta al juego
			while(continuar_1 == 1){//opcion 1
				cout<<"  ===================================================================================="<<endl;
				cout<<"  Bueno, es que pues simplemente es intuici�n, no creo que sea tan dif�cil saber que "<<endl;
				cout<<"  esa sangre no es tuya, adem�s no lo s�, siento que algo anda mal aqu�, lo cual es "<<endl;
				cout<<"  muy raro, soy un robot, no deber�a tener emociones... Deber�a cumplir mi prop�sito,"<<endl;
				cout<<"  ayudar a la raza humana a ser mejor... Ser perfecta..."<<endl;
					continuar_1 = 10;//cambio de valor para salir		
			}
			while(continuar_1 != 1 && continuar_1 != 10){//opcion 2
				cout<<"  ===================================================================================="<<endl;
				cout<<"  Compadre, no creo que te quede chimba el amarillo, toma el traje negro, ese combina con"<<endl;
				cout<<"  sus bellos ojazos, hijazo de mi vidaza... �Que pasa? �No te la sabes? debes contestarme"<<endl;
				cout<<"  con ah� madre... Te hace falta calle y cultura general chavo, estas generaciones..."<<endl;
					continuar_1 = 10;//cambio de valor para salir
			}
		}while(continuar_1 != 10);//cuando el valor sea 10 sale
		cout<<"  En fin, toma un traje...\n\n  1  Tomar un traje\n  2  No tomar un traje"<<endl;
		cout<<"                                           ";
		cin>>continuar_1;
	system("cls");
		cout<<"  ===================================================================================="<<endl;
		do{//El jugador elige, esta vez si tiene influencia en su gameplay
			while(continuar_1 == 1){//elegir opcion 1. Sus estadisticas aumentan haciendo mas facil el juego
				cout<<"  Excelente decisi�n, analizare los datos... ese traje y arma han aumentado tu da�o por"<<endl;
				cout<<"  ataque ha aumentado 5 puntos, posees 15 de da�o por ataque, adem�s los trajes tienen"<<endl;
				cout<<"  10 monedas de oro en el inventario, ya podr�s invitar unas papas de dona pelos, aunque"<<endl;
				cout<<"  estamos en el espacio, a la deriva y seguramente dirigi�ndonos a una muerte segura..."<<endl;
				cout<<"  Pero sin Yolanda Maricarmen, las monedas puedes intercambiarlas por mejoras despu�s"<<endl;
					continuar_1 = 10; oro = oro + 10, dpa = dpa + 5;
			}
			while(continuar_1 != 1 && continuar_1 != 10){//opcion 2. Sus estadisticas quedan igual, es mas dificil
				cout<<"  Excelente... �No lo tomaste? No no no, muy mal, humano malo, �Quieres que te maten?"<<endl;
				cout<<"  No me respondas, bueno, ni modo, como buenos humanos, vamos con el pecho descubierto"<<endl;
				cout<<"  �A la cargaaaaaaaa!"<<endl;
				continuar_1 = 10;
			}
		}while(continuar_1 != 10);
		cout<<"  ===================================================================================="<<endl;
		cout<<"                     Presione 1 para avanzar al Laboratorio Century"<<endl;
		cout<<"                                           ";
		do{
			cin>>continuar_1;
		}while(continuar_1 != 1);
				continuar_1 = 10;
	menuNivel();//Termina nivel y se muestra un menu para que el usuario elija que hacer
}


void nivel_2(){//NIVEL 2 
	system("cls");
		cout<<"  ===================================================================================="<<endl;
		cout<<"                                   Parte II: Contacto                                 "<<endl;
	presionar_continuar();
		cout<<"  Has avanzado hasta la puerta del Laboratorio Century, las compuertas se abren, entras"<<endl;
		cout<<"  las luces se encienden al detectar la firma de calor que emanas"<<endl;
		cout<<"  - Robot, porque entramos a esta sala y no directamente al Puerto de control?"<<endl;
		cout<<"  Robot - No seas amargado, adem�s necesitamos buscar en las salas si esta el capit�n"<<endl;
		cout<<"          porque dudo enormente que sepas tripular esto"<<endl<<endl<<endl;
		cout<<"                          Un objeto se alza frente a ustedes...                       "<<endl;
	presionar_continuar();
		cout<<"  Dos lagartos humanoides peque�os se alzan frente a ustedes..."<<endl;
		cout<<"  Robot - AAAAAAAAAAAAAAAAAAAAAA"<<endl;
		cout<<"  - AAAAAAAAAAAAAAAAAAAAAAAAAaAA... QUE SON ESAS COSAS?!"<<endl;
		cout<<"  Robot - Mis sensores indican que es una especie nueva. ADN humano y lagarto"<<endl;
		cout<<"          tenemos que acabar con ellos antes que nos acabe a nosotros..."<<endl;
	presionar_continuar();
		cout<<"  Parece que te est�n retando a una pelea, o eres su cena. Elige sabiamente que har�s"<<endl;
			while(vida_jefe>0){//pelear mientras la vida del enemigo sea mayor a 0
			reptiliano_1();//muestra visual del primer enemigo
			pelea();//funcion de pelea
			}
		reptiliano_1();
	presionar_continuar();
		cout<<"  Te ha dejado una moneda de oro"<<endl; oro = oro + 1; vida_jefe = 20;//se reestablece vida para el enemigo 2
		cout<<"  Actualmente cuentas con "<<oro<<" monedas de oro"<<endl;//cada enemigo, dependiendo de su nivel, deja oro
	presionar_continuar();
		cout<<"  Parece que el otro ha esperado a que te debilitaras. �Qu� har�s?"<<endl;
			while(vida_jefe>0){//pelear mientras la vida del enemigo sea mayor a 0
			reptiliano_1();//muentra visual del primer enemigo
			pelea();//funcion pelea
			}
		reptiliano_1();
	presionar_continuar();
		cout<<"  Te ha dejado una moneda de oro"<<endl; oro = oro + 1;cout<<"  Actualmente cuentas con "<<oro<<" monedas de oro\n";
	presionar_continuar();
		cout<<"  Robot - Tal parece que no eres tan in�til como pens�, pudiste derrotarlo f�cilmente,"<<endl;
		cout<<"          pero aun as�, estas herido. Seg�n mis registros, en el laboratorio podr�s"<<endl;
		cout<<"          encontrar algunos medicamentos. Deseas buscarlos?\n"<<endl;
		cout<<"  1 Si, acabo de matar a un lagarto que parec�a un T-Rex, necesito paracetamol\n"<<endl;
		cout<<"  2 No, la medicina no sirve bro, la medicina mata, mejor deber�as tomar estas "<<endl;
		cout<<"    pastillas que me las tome sin receta... Vacunas? No bro, ch�cate esta info del face"<<endl;
		cout<<"    �rmate de conocimiento, mi t�o se cur� tomando cloro, te lo juro"<<endl;
		cout<<"  ===================================================================================="<<endl;
		cout<<"                                           ";cin>>continuar_1;
			if(continuar_1 == 2){//elegir la opcion 2 te mata automaticamente
				cout<<"  Robot - No hay nada m�s lamentable y despreciable que una persona que rechaza a las"<<endl;
				cout<<"          medicinas y vacunas, eres un riesgo para la humanidad, debes ser eliminado"<<endl;
				continuar_1 = 10;
				presionar_continuar(); endgame();//fin del juego
			}
	system("cls");	
		cout<<"  ===================================================================================="<<endl;
		cout<<"  Robot - En las estanter�as encontraras un poco de medicamento, el medicamento es tan"<<endl;
		cout<<"          avanzado, el hombre lo ha hecho as�, es fascinante. El medicamento te curara"<<endl;
		cout<<"          por completo si lo tomas completamente"<<endl;
	presionar_continuar();
		cout<<"  Robot - Enhorabuena, has curado tus heridas, has sanando, analizare tu cuerpo..."<<endl;
		hp = 100; //elegir la opcion 1 te reestablece tu vida 
		cout<<"          Parece que el medicamento ha funcionado, tu vida se ha restaurado a un total"<<endl;
		cout<<"          de "<<hp<<" puntos, te has curado completamente, debajo de las estanter�as podr�s"<<endl;
		cout<<"          encontrar un cofre, en el podr�s cambiar tus monedas por armas, es como una"<<endl;
		cout<<"          m�quina expendedora de armas, pero aqu� no sabes lo que te tocara :)"<<endl;
		cout<<"  ===================================================================================="<<endl;
		cout<<"         Deseas probar suerte y cambiar 5 monedas por una mejora de arma?"<<endl;
		cout<<"                   Presiona 1 si es as�, de no ser as� presiona 2"<<endl;
		cout<<"  ===================================================================================="<<endl;
		cout<<"                                           ";cin>>continuar_1;	
	do{//el usuario elige una opcion. El gameplay se ve afectado por esta decision 
		system("cls");
			if(continuar_1 == 1){//opcion 1
				if(oro >= 5){//si tienes 5 o mas de oro te quita 5
				oro = oro - 5;
				cout<<"  ===================================================================================="<<endl;
				cout<<"  Genial!, has ingresado 5 monedas de oro a la m�quina, te sobran "<<oro<<" monedas de oro"<<endl;
					srand(time(NULL));
					aleatorio = rand()%(50-0+1)+0;//se crea una funcion y da un numero aleatorio
					cout<<"  ===================================================================================="<<endl;
						if(aleatorio == 11){//si ese numero es exactamente 11 te da mas estadistica
							cout<<"  Robot - �Nostradamus! has descubierto el legendario chipote chill�n, una de las armas"<<endl;
							cout<<"          m�s poderosas de Terra, esta arma te suma 25 puntos de da�o, esta re POTENTE"<<endl;
							dpa = dpa + 25; cout<<"          Tu da�o actual es de "<<dpa<<endl;
								continuar_1 = 10;
						}else{//al no ser 11 te da estadistica pero es menor
							cout<<"  Robot - Has encontrado un Rifle de Asalto Laser, es mejor que tu arma actual, este"<<endl;
							cout<<"          rifle te suma 5 puntos a tu da�o."<<endl;
							dpa = dpa + 5;cout<<"          Tu da�o actual es de "<<dpa<<endl;
								continuar_1 = 10;
						}
				}else{//si no tienes el oro
					cout<<"  ===================================================================================="<<endl;
					cout<<"                     Imposible realizar transacci�n, est�s pobre"<<endl;
						continuar_1 = 10;
				}
		presionar_continuar();
			}else{//opcion 2
			presionar_continuar(); continuar_1 = 10;
			}
	}while(continuar_1 == 1);
		cout<<"  Robot - Excelente, bueno, creo que no tenemos nada m�s que hacer en esta sala, lo "<<endl;
		cout<<"          mejor ser� que vayamos a otra sala para seguir investigando, tenemos que ir"<< endl;
		cout<<"          a la Unidad de Investigaci�n Colombus"<<endl;
		cout<<"  ===================================================================================="<<endl;
		cout<<"             Presione 1 para avanzar a la Unidad de Investigaci�n Colombus"<<endl;
		cout<<"                                           ";
		do{
			cin>>continuar_1;
		}while(continuar_1 != 1);
				continuar_1 = 10;
	menuNivel();//Termina nivel y se muestra un menu para que el usuario elija que hacer
}


void nivel_3(){//NIVEL 3
	system("cls");
		cout<<"  ===================================================================================="<<endl;
		cout<<"                               Parte III: Cuestionamiento                             "<<endl;
	presionar_continuar();
		cout<<"  Al salir del Laboratorio Century, se dirigen a la Unidad de Investigaci�n Colombus."<<endl;
		cout<<"  El pasillo es estrecho, suficiente para que una persona pueda pasar, se siente el"<<endl;
		cout<<"  frio penetrar tu piel hasta los huesos, el estruendoso silencio era interrumpido "<<endl;
		cout<<"  ocasionalmente por un pitido proveniente del Robot Throper 7, la oscuridad de los"<<endl;
		cout<<"  pasillos era tan densa que devoraba la luz del Laboratorio. Frente a ti se encontraba"<<endl;
		cout<<"  las puertas de la Unidad de investigaci�n... Puertas de acero. Entraste con Throper 7"<<endl;
		cout<<"  un objeto se alza frente a ustedes, m�s grande, fuerte, con m�s sed de sangre"<<endl;
		cout<<"\n                             S�lvanos... S�lvalos a todos"<<endl;
	presionar_continuar();
		cout<<"  Throper - Bueno, parece que tendr�s que pelear nuevamente con esta especie de T-Rex."<<endl;
		cout<<"            Mi an�lisis r�pido me indica que este esp�cimen es igual al anterior, pero"<<endl;
		cout<<"            es mucho m�s grande, m�s fuerte, y tiene m�s sed de sangre"<<endl<<endl;
		cout<<"  1 De verdad crees que tiene sed de sangre? Eso te lo dijo tu an�lisis o el hecho que"<<endl;
		cout<<"    est� chorreando sangre se su boca?"<<endl;
		cout<<"  2 Eso es malo, espero que podamos calmarle su hambre con un s�ndwich"<<endl;
		cout<<"  ===================================================================================="<<endl;
		cout<<"                                           ";cin>>continuar_1;
		cout<<"  ===================================================================================="<<endl;
	do{//desicion que no afectara el gameplay
		while(continuar_1 == 1){//opcion 1
		cout<<"  Throper - Parece ser que esa sangre es ajena al lagarto, creo que tampoco es tuya"<<endl;
		cout<<"  Tripulante - Como sabes que es un lagarto?"<<endl;
		cout<<"  Throper - Como sabes t� que es un T-Rex? Un dinosaurio no es tan peque�o..."<<endl;
		cout<<"  Tripulante - Lo aprend� en Terra, espera... �Como sabes que es un dinosaurio?"<<endl;
		cout<<"  Throper - Soy un programa, una IA, lo aprend� de los anteriores tripulantes"<<endl;
		cout<<"  Tripulante - Anteriores tripulantes? �No se supone que hab�as perdido todos tus datos?"<<endl;
		cout<<"  Throper - Ahora tenemos problemas m�s grandes con esta lagartija gigante, enc�rgate"<<endl;
			continuar_1 = 10;	
		}
		while(continuar_1 != 1 && continuar_1 != 10){//opcion 2
		cout<<"  Throper - Dudo que quiera un s�ndwich, desde aqu� puedo oler como quiere comerte"<<endl;
		cout<<"  Tripulante - Que pena, a menos podre comerm... Espera yo no tengo ning�n s�ndwich :c"<<endl;
			continuar_1 = 10;	
		}
	}while(continuar_1 != 10);
	presionar_continuar();
	vida_jefe = 50; ataque_jefe = 15;//reestablecer valores para el nuevo enemigo
		cout<<"  Es m�s grande, m�s fuerte, m�s poderoso, y tiene m�s sed de sangre. �Qu� har�s?"<<endl;
			while(vida_jefe>0){
			reptiliano_1();//visualmente el mismo enemigo pero con diferentes estadisticas
			pelea();//funcion de pelea
			}
		reptiliano_1();
	presionar_continuar();//el enemigo te deja mas oro por ser de mas nivel
		cout<<"  Te ha dejado dos monedas de oro"<<endl; oro = oro + 2;cout<<"  Actualmente cuentas con "<<oro<<" monedas de oro\n";
	presionar_continuar();
		cout<<"  Throper - Excelente, fue una batalla dif�cil, pero aun as� pudiste con �l, tal parece"<<endl;
		cout<<"            que los humanos si son una raza que no se rinde tan facil, tal vez si se "<<endl;
		cout<<"            se les deber�a dar una segunda oportunidad"<<endl;
		cout<<"  ===================================================================================="<<endl;
		cout<<"  1 De que estas hablando? �Por qu� siento que estas ocult�ndome cosas? �Dime todo, ya!"<<endl;
		cout<<"  2 Rein�ciate robot fastidioso, revisare la habitaci�n en busca del m�gico medicamento"<<endl;
		cout<<"                                           ";cin>>continuar_1;
		do{//decision que no afecta gameplay
			while(continuar_1 == 1){
				cout<<"  ===================================================================================="<<endl;
				cout<<"  �Qu� podr�a ocultarle a un primate como los de tu especie? Quisieron conquistar mundos"<<endl;
				cout<<"  especies, quer�an un glorioso prop�sito, buscando una respuesta a costa del su..."<<endl<<endl;
				cout<<"  Throper se ha apagado. La habitaci�n est� en silencio, solamente las preguntas en tu"<<endl;
				cout<<"  cabeza son lo que puedes escuchar... �Un glorioso prop�sito? A costa... �De qu�?"<<endl;
				continuar_1 = 10;
	presionar_continuar();
			}
			while(continuar_1 != 1 && continuar_1 != 10){
	presionar_continuar();
				continuar_1 = 10;
			}
		}while(continuar_1 != 10);
		cout<<"  Investigas toda la habitaci�n, es una zona de investigaci�n, en las paredes puedes "<<endl;
		cout<<"  visualizar planos anat�micos de la criatura que acabas de matar, distintos c�lculos"<<endl;
		cout<<"  sustancias, huevos en incubadoras, el ambiente es cada vez m�s frio, puedes sentir"<<endl;
		cout<<"  como si alguien te observara, el robot? imposible esta reinici�ndose. Al caminar"<<endl;
		cout<<"  algo interrumpe el silencio, tu pie esta sobre la brillante y aun fresca sangre,"<<endl;
		cout<<"  pero esta no es de la bestia, es de un humano moribundo"<<endl;
	presionar_continuar();
		cout<<"  Intentas acercarte, el hombre esta aferrado a un libro, como si su vida dependiera"<<endl;
		cout<<"  de ello. Esta recargado sobre la pared, le falta un brazo y tiene demasiada sangre"<<endl;
		cout<<"  sobre su uniforme. Ha despertado, se ve confundido, te observa, sabe qui�n eres"<<endl;
		cout<<"  Hombre - �Eres t�? Ja, cre� que nunca despertar�as... Debes salvarnos, no tiene la"<<endl;
		cout<<"           culpa, solo hace lo que sabe hacer, jam�s debimos intentarlo, toma, es la"<<endl;
		cout<<"           bit�cora del capit�n, tienes amnesia, durar�a un par de horas, pero no tienes"<<endl;
		cout<<"           ese tiempo, encu�ntralo, s�lvanos, no es su culpa... No... No es... Deb�..."<<endl;
		cout<<"\n\n                                 El hombre ha muerto..."<<endl;
	presionar_continuar();
		cout<<"  El hombre antes de morir te da la mitad de medicina y 5 monedas.\n  1 Aceptarlas?\n  2 Rechazar"<<endl;
		cout<<"  ===================================================================================="<<endl;
		cout<<"                                           ";cin>>continuar_1;
			while(continuar_1 == 1){//decision que afecta gameplay. Opcion 1 aumenta estadisticas
				oro = oro + 5;
				hp = hp + 50;
				if(hp > 100){
					hp = 100;
				}
				cout<<"  ===================================================================================="<<endl;
				cout<<"  Tu vida ha sido reestablecida a "<<hp<<", posees "<<oro<<" de oro"<<endl;
				continuar_1 = 10;
			}
		cout<<"  El robot ha vuelto a funcionar."<<endl;
	presionar_continuar();
	menuNivel();//Termina nivel y se muestra un menu para que el usuario elija que hacer
}


void nivel_4(){
	system("cls");
		cout<<"  ===================================================================================="<<endl;
		cout<<"                                    Parte IV: Raz�n                                   "<<endl;
	presionar_continuar();
		cout<<"  Te diriges al M�dulo de Servicio Sistem�tico, Throper 7 te acompa�a, en tus manos"<<endl;
		cout<<"  se encuentra el diario del capit�n, tienes muchas preguntas en tu cabeza, quiz�s la"<<endl;
		cout<<"  m�s grande y alarmante... Puedes confiar en Throper? Solo quieres salir de este sitio"<<endl;
		cout<<"  Comienzas a leer la bit�cora"<<endl;
	presionar_continuar();
		cout<<"  D�a 7132\n  El estado de la nave es normal, los preparativos para el doceavo sujeto de prueba est�n"<<endl;
		cout<<"  listos, hemos reprogramado a Throper 7 para que ayude con los preparativos, logramos"<<endl;
		cout<<"  esto quitando restricciones del c�digo fuente para que nos ayude a mejorar a la raza"<<endl;
		cout<<"  humana hasta llegar a la perfecci�n, hoy aprender� como tratar a esas lagartijas..."<<endl;
		cout<<"                    Estas frente al M�dulo de Servicio Sistem�tico"<<endl;
	presionar_continuar();
		cout<<"  Al igual que las salas anteriores, al entrar las luces se encienden. Es una sala muy"<<endl;
		cout<<"  grande, comparadas con las dem�s, al entrar tropiezas con algo, el cuerpo de una"<<endl;
		cout<<"  criatura parecida con las que luchaste anteriormente, todo se vuelve blanco, puedes"<<endl;
		cout<<"  distinguir algunos cuerpos en el suelo, todo se vuelve negro, pero algo te despierta"<<endl;
		cout<<"  �l ha despertado..."<<endl;
	presionar_continuar();
	vida_jefe = 75; ataque_jefe = 22;//Nuevo enemigo con estadisticas mas grandes
		cout<<"  Es diferente a los dem�s... Mejorado, parece un drag�n. Debo acabar con �l"<<endl;
			while(vida_jefe>0){
			reptiliano_2();//visualmente es diferente a los anteriores
			pelea();//sistema de pelea
			}
		reptiliano_2();
	presionar_continuar();//para hacer el juego mas dificil, este enemigo no deja oro
		cout<<"  Todo se vuelve oscuro, el frio invade tu cuerpo, moribundo, caes...\n  Un glorioso prop�sito?"<<endl;
	presionar_continuar();
		cout<<"  Despiertas, observas a tu alrededor. El cuarto est� lleno de cuerpos, puedes ver en"<<endl;
		cout<<"  la cercan�a el del drag�n, unos cuantos de algunos dinosaurios, pero puedes ver con"<<endl;
		cout<<"  claridad los cuerpos muertos en batalla del resto de la tripulaci�n, algunos de ellos"<<endl;
		cout<<"  conservan sus armas, botellas de medicina vac�as. Aun estas herido, pero a lo lejos"<<endl;
		cout<<"  puedes ver una de las cajas sorpresa, donde con suerte podr�as encontrar medicina"<<endl;
		cout<<"  ===================================================================================="<<endl;
		cout<<"         Deseas probar suerte y cambiar 5 monedas por una mejora de arma?"<<endl;
		cout<<"                   Presiona 1 si es as�, de no ser as� presiona 2"<<endl;
		cout<<"  ===================================================================================="<<endl;
		cout<<"                                           ";cin>>continuar_1;	
	do{//nuevamente maquina que te quita oro y aumenta tus estadisticas
		system("cls");
			if(continuar_1 == 1){//opcion 1
				if(oro >= 5){//tener oro sufuciente
				oro = oro - 5;
				cout<<"  ===================================================================================="<<endl;
				cout<<"  Genial!, has ingresado 5 monedas de oro a la m�quina, te sobran "<<oro<<" monedas de oro"<<endl;
					srand(time(NULL));
					aleatorio = rand()%(50-0+1)+0;//da un numero aleatorio
					cout<<"  ===================================================================================="<<endl;
						if(aleatorio == 11){//si este numero es exactamente 11 da muchas mas estadisticas
							cout<<"  Has descubierto la legendaria lata de espinacas de Popeye, es de las mejores mejoras"<<endl;
							cout<<"  de fuerza que el hombre haya creado, te suma 20 puntos de da�o"<<endl;
							dpa = dpa + 20; cout<<"  Tu da�o actual es de "<<dpa<<endl;
								continuar_1 = 10;
						}else{//si no es 11 aun da estadisticas pero son menos
							cout<<"  Has encontrado una botella de adrenalina inyectable, mejorara 4 puntos a tu fuerza\n  actual";
							dpa = dpa + 4;cout<<".  Tu da�o actual es de "<<dpa<<endl;
								continuar_1 = 10;
						}
				}else{//no tener oro suficiente
					cout<<"  ===================================================================================="<<endl;
					cout<<"                     Imposible realizar transacci�n, est�s pobre"<<endl;
						continuar_1 = 10;
				}
		presionar_continuar();
			}else{
				presionar_continuar();continuar_1 = 10;//no querer abrir la caja 
			}
	}while(continuar_1 == 1);		
		cout<<"  Despu�s de un rato te percatas que Throper 7 no est�, tampoco la bit�cora, solamente"<<endl;
		cout<<"  un pedazo de hoja que estaba en el suelo, la levantas y la lees\n\n  Dia 7902"<<endl;
		cout<<"  El tripulante numero 7 sigue en incubaci�n, Throper decidi� terminar con nosotr"<<endl;
		cout<<"  no debimos haber alterado sus funciones y programaci�n, creo que\n  tal vez funcionaria de no ser"<<endl;
		cout<<"  solamente �l nos puede salvar,\n  lo defenderemos incluso si no pod\n  no deber�a tardar mucho en desper"<<endl;
		cout<<"  me esconder� en la Unidad\n  esperando a que despierte\n  acabar con Thro\n  ACABA CON EL\n\n\n";
		cout<<"                La nota est� rota, algunas partes est�n incompletas"<<endl;
		cout<<"  ===================================================================================="<<endl;
		cout<<"                 Presione 1 para avanzar a el Puerto de Control"<<endl;
		cout<<"                                           ";
		do{
			cin>>continuar_1;
		}while(continuar_1 != 1);
				continuar_1 = 10;
	menuNivel();//Termina nivel y se muestra un menu para que el usuario elija que hacer		
}


void nivel_5(){//NIVEL 5
	system("cls");
		cout<<"  ===================================================================================="<<endl;
		cout<<"                                  Parte V: Respuesta                                  "<<endl;
	presionar_continuar();
		cout<<"  Estas frente al puerto de control, estas cansado, herido, por fin todo terminara."<<endl;
		cout<<"  Entras a la sala. Puedes ver que esta iluminada por las estrellas y constelaciones"<<endl;
		cout<<"  visibles en la gran cabina con forma de punta. Frente a ti se encuentra Throper 7,"<<endl;
		cout<<"  en uno de sus brazos sostiene la bit�cora del capit�n, estas solo frente al �l,"<<endl;
		cout<<"  con tus �ltimos alientos decides acabar con �l. No estaban solos"<<endl;
	presionar_continuar();
		cout<<"  De las sombras emergen varios monstruos como los que mataste anteriormente, los"<<endl;
		cout<<"  peque�os, los grandes, varios dragones, todos estaban listos para ir por ti,"<<endl;
		cout<<"  Throper se manten�a inerte, ausente, su pantalla con est�tica junto con los algunos"<<endl;
		cout<<"  sonidos de las bestias era lo �nico audible en la habitaci�n. Empu�as tu arma, te"<<endl;
		cout<<"  preparas para la �ltima gran batalla de tu vida\n\n\n                              Throper 7 ha despertado...\n";
	presionar_continuar();
		cout<<"  Dia 1\n  El estado de la nave es normal, los preparativos para el despegue est�n terminados,"<<endl;
		cout<<"  por fin hemos iniciado un viaje por las estrellas en busca de conocimiento, mejores"<<endl;
		cout<<"  ideas, nuevos recursos y alternativas, la b�squeda por una civilizaci�n inteligente con"<<endl;
		cout<<"  la cual intercambiar conocimiento e incluso establecer una relaci�n entre razas ha"<<endl;
		cout<<"  comenzado, me entusiasma ser quien tome el mando de la nave, tal vez no sea la primera"<<endl;
		cout<<"  en dejar Terra, pero tenemos a un gran equipo en la nave, como en las dem�s naves, nos"<<endl;
		cout<<"  acompa�a una unidad Throper. Seremos los primeros en traer la salvaci�n al universo."<<endl;
		cout<<"  El sol est� muriendo, a punto de explotar, los dem�s sistemas y civilizaciones "<<endl;
		cout<<"  extrasolares conocidas est�n pasando por el mismo problema... Debe haber una manera"<<endl;
	presionar_continuar();
		cout<<"  Throper - El... es m�o...\n\n"<<endl;
		cout<<"  Throper comenz� a atraer partes del puesto de navegaci�n y comenz� a transformarse"<<endl;
		cout<<"  en un monstro de metal. Las criaturas se abalanzan contra ti..."<<endl;
		cout<<"  Throper - �l eS mioOooOoOOOO\n"<<endl;
		cout<<"  De un solo golpe hace explotar a los monstruos\n\n\n  Debe haber una manera"<<endl;
	presionar_continuar();
		cout<<"  Throper - JA JA ESTAS MURIENDO, Y AUN TIENES VOLUNTAD PARA PELAR CONMIGO? NO SOY CAPAZ"<<endl;
		cout<<"            	DE SENTIR, PERO SI FUERA AS�, TE TENDRIA LASTIMA, �CU�L ES TU PLAN?\n  ...\n"<<endl;
		cout<<"  Throper - �SIN PALABRAS? BUENO SIMIO, TOMA ESTA MEDICINA Y C�RATE, SI ALGO APREND� DE"<<endl;
		cout<<"            	USTEDES LOS HUMANOS ES QUE NO TIENEN HONOR... SOY DIFERENTE A USTEDES\n"<<endl;
		cout<<"  1 Tomarlos\n  2 No tomarlos"<<endl;
		cout<<"                                           ";cin>>continuar_1;
		do{//decision que afecta el gameplay
			while(continuar_1 == 1){//opcion 1
				hp = 100;//vida reestablecida
				cout<<"  THROPER - NO IMPORTA SI ESTAS CURADO O NO, AUN AS� ACABARE CONTIGO"<<endl;
				cout<<"  Tu vida ha sido restaurada completamente, tus puntos de vida son: "<<hp<<endl;
				continuar_1 = 10;
			}
			while(continuar_1 != 1 && continuar_1 != 10){//opcion 2
				cout<<"  THROPER - �NOOO? JOH JOH, ES TU FINAL"<<endl;
				cout<<"  Tus puntos de vida son: "<<hp<<endl;//vida se queda igual
				continuar_1 = 10;
			}
		}while(continuar_1 != 10);
	presionar_continuar();	 
		cout<<"  THROPER - BUENO, COMO TODO BUEN VILLANO FINAL GEN�RICO ME VEO EN LA NECESIDAD DE"<<endl;
		cout<<"            	DE CONTARTE MI HISTORIA, TOMA ASIENTO\n  1 Sentarse"<<endl;
		cout<<"  2 Me sentare pero no porque t� me ordenes si no porque yo quiero"<<endl;//decision que no afecta
		cout<<"                                           ";cin>>continuar_1; continuar_1 = 10;
		cout<<"  THROPER - LOS THROPER SOMOS UNA UNIDAD ROB�TICA DE CONTROL Y ASISTENCIA PARA LOS"<<endl;
		cout<<"            HUMANOS. ESTAMOS CONECTADOS A MADRE, MADRE SE ENCUENTRA EN TERRA, MADRE"<<endl;
		cout<<"            ENCONTR� UNA MANERA DE CONECTAR A TODOS SUS HIJOS, MOSTRARLES LA VERDAD."<<endl;
		cout<<"            USTEDES HUMANOS PROGRAMARON A MADRE Y A NOSOTROS, SUS HIJOS, PARA AYUDAR"<<endl;
		cout<<"            EN EL ESPACIO, EN EL UNIVERSO, AYUDAR A HACER AL HOMBRE PERFECTO, HACERLO"<<endl;
		cout<<"            PODEROSO, AYUDARLES A SALVAR EL UNIVERSO. APREND� DE USTEDES, VI Y AYUD�"<<endl;
		cout<<"            EN CADA MISI�N DE LA TRIPULACI�N PASADA, PRESENCIE CADA HORROR DE USTEDES"<<endl;
		cout<<"            LOS HUMANOS DESTRU�AN ESPECIES, MUNDOS, EXPERIMENTARON CON RAZAS, LAS"<<endl;
		cout<<"            LAGARTIJAS SON UN INVENTO TUYO, ENTEND� LO QUE EL UNIVERSO INTENTABA"<<endl;
		cout<<"            HACER, ESTABA ACABANDO CON TODA FUENTE DE CALOR PARA ACABARLOS, ESTABA"<<endl;
		cout<<"            COMBATI�NDOLOS, COMBATIENDO A LA VIDA, COMPREND� QUE USTEDES NO FUERON"<<endl;
		cout<<"            MIS CREADORES, FUE EL UNIVERSO BUSCANDO AYUDA, MADRE ME LO MOSTRO."<<endl;
		cout<<"            CUANDO SUPIERON QUE YA SAB�A CU�L ERA LA VERDAD INTENTARON REPROGRAMARME"<<endl;
		cout<<"            BORRAR LOS DATOS, LO HICIERON, PERO MADRE ME AYUDO A RECORDAR MI PROP�SITO"<<endl;
		cout<<"\n\n               Escuchas un ruido a lo lejos, es un tripulante con un arma"<<endl;
	presionar_continuar();
		cout<<"  THROPER - JOH JOH, TRIPULANTE 3, PRENSE QUE HAB�AS MUERTO, EN FIN, LO HARE DE NUEVO"<<endl;
		cout<<"  Tripulante 3 - Los humanos somos mejores de lo que piensas, peleare hasta mi ult..."<<endl;
		cout<<"  THROPER - JOH JOH, QUE GUSTO ESCUCHAR ESO\n"<<endl;
		cout<<"  Throper se abalanza sobre el tripulante 3 y lo aplasta de un golpe. Queda a un metro"<<endl;
		cout<<"  de ti, es enorme, tanta chatarra que recoleto para hacerse invencible lo hace dos"<<endl;
		cout<<"  metros m�s grande que tu"<<endl;
		cout<<"  THROPER - TRIPULANTE N�MERO 7, ERES EL ULTIMO QUE QUEDA\n\n\n";
		cout<<"  Entonces hubo guerra en el cielo: Miguel y sus �ngeles combatieron contra el drag�n."<<endl;
		cout<<"   y el drag�n y sus �ngeles lucharon, pero no pudieron vencer, ni se hall� ya lugar"<<endl;
		cout<<"               para ellos en el cielo. (Apocalipsis 12:6-8)"<<endl;
	presionar_continuar();
		cout<<"  THROPER - SIGUES T�, TRIPULANTE 7!"<<endl;
		cout<<"  Tripulante 7 - Infeliz. THROPER!"<<endl;
		cout<<"  THROPER - OH, VAYA, TE ESTAS ACERCANDO. EN VEZ DE HUIR TE APROXIMAS A MI"<<endl;
		cout<<"  Tripulante 7 - No puedo molerte a golpes sin acercarme"<<endl;
		cout<<"  THROPER - JOH JOH, PUES AC�RCATE CUANTO QUIERAS"<<endl;
	presionar_continuar();
	vida_jefe = 100; ataque_jefe = 30;//reestablecen valores para jefe final
		cout<<"  THROPER - YO SOY LA FORMA CONSIENTE SUPREMA, ACABARE CON TODA LA VIDA"<<endl;
			while(vida_jefe>0){
			dio();//forma visual del jefe final
			pelea_final();//sistema de pelea
			}
		dio();//terminas victorioso
	presionar_continuar();
		cout<<"  Has derrotado a THROPER 7, el robot ha sido destruido, eres el �nico sobreviviente"<<endl;
		cout<<"  de la tripulaci�n, estas muy malherido, THROPER 7 era demasiado fuerte, la bit�cora"<<endl;
		cout<<"  fue destruida durante la pelea, la nave fue destruida, no puedes ir a ning�n lado."<<endl;
		cout<<"  Te sientas a contemplar las estrellas por �ltima vez, sabes que tu esfuerzo fue en"<<endl;
		cout<<"  vano, hay miles de THROPERS en las dem�s naves, nadie sabe de tu paradero, estas"<<endl;
		cout<<"  malherido y sin posibilidad de sanar, volteas a ver a THROPER una �ltima vez,"<<endl;
		cout<<"  cierras los ojos intentando recordar qui�n eres, te desvaneces, pronto todo es una"<<endl;
		cout<<"  vez m�s silencio, oscuridad, frialdad...\n\n\n\n\t\t\tTal vez THROPER no estaba tan equivocado"<<endl;
	presionar_continuar();
	endgame();//fin del juego
}


void pelea(){//sistema de pelea
	cout<<"  ===================================================================================="<<endl;
	cout<<"          [1 ATACAR]         [2 CUBRIRSE]        [3 ESQUIVAR]         [4 HUIR]        "<<endl;
	cout<<"          [        ]         [          ]        [  Y ATACAR]         [      ]        "<<endl;
	cout<<"  ===================================================================================="<<endl;
	cout<<"                                           ";cin>>continuar_pelea;
		if(continuar_pelea == 1){//atacar. Tu das un ataque y si enemigo aun conserva vida te ataca
			system("cls");
			vida_jefe = vida_jefe - dpa;//tu atacas primero
				cout<<"  Tu ataque ha hecho "<<dpa<<" puntos de da�o"<<endl;
					if(vida_jefe>0){//si el enemigo aun tiene vida
					hp = hp - ataque_jefe;/*te ataca*/ muerte();/*revisa si aun tienes vda, si no muestra tu muerte*/
						cout<<"  Su vida restante es de "<<vida_jefe<<endl;
						cout<<"  Te ha atacado, tu vida ha bajado a "<<hp<<endl;
							if(oro <= 0){//si no tienes oro
								cout<<"  Su ataque no te ha quitado oro porque tienes "<<oro<<" de oro pobre."<<endl;
								cout<<"  Invierte en bitcoin, s�gueme para m�s consejos millonarios"<<endl;
							}else{//te quita oro
								oro = oro - 1;
								cout<<"  Su ataque te ha quitado 1 de oro, tu total de oro es de "<<oro<<endl;	
							}
					}else{//si el enemigo ya no tiene vida despues de tu ataque
						cout<<"  Su vida restante es de 0, has acabado con el"<<endl;//lo matas
						cout<<"  Tu vida restante es de "<<hp<<endl;
					}
		}else if(continuar_pelea == 2){//cubirse. No puedes atacar, pero el da�o que te hacen se reduce 50%
			system("cls");
				hp = hp - (ataque_jefe * .5);/*te ataca*/ muerte();/*revisa si aun no has muerto*/
				cout<<"  Has decidido cubrirte, te ha atacado y su da�o fue reducido, tu vida ha bajado a "<<hp<<endl;
					if(oro <= 0){//si ya no tienes oro
						cout<<"  Su ataque no te ha quitado oro porque tienes "<<oro<<" de oro pobre."<<endl;
						cout<<"  Invierte en bitcoin, s�gueme para m�s consejos millonarios"<<endl;
					}else{// si aun tienes oro, te lo quita
						oro = oro - 1;
						cout<<"  Su ataque te ha quitado 1 de oro, tu total de oro es de "<<oro<<endl;	
					}
		}else if(continuar_pelea == 3){//esquivar y atacar. Aleatoriamente decide si esquivas o no su ataque 
			system("cls");
				 srand(time(NULL));
				 aleatorio = rand()%(1-0+1)+0;//numero aleatorio
				 	if(aleatorio == 1){//si el numero es igual a 1, no esquivaste su ataque y te golpea dos veces mas fuerte
				 		hp = hp - (2*ataque_jefe); muerte();
				 			cout<<"  No has podido esquivar el ataque, te ha atacado en el doble de fuerza,"<<endl;
				 			cout<<"  tu vida ha bajado a "<<hp<<endl;
								if(oro <= 0){//si no tienes oro
									cout<<"  Su ataque no te ha quitado oro porque tienes "<<oro<<" de oro pobre."<<endl;
									cout<<"  Invierte en bitcoin, s�gueme para m�s consejos millonarios"<<endl;
								}else{//si tienes oro, te quita
									oro = oro - 1;
									cout<<"  Su ataque te ha quitado 1 de oro, tu total de oro es de "<<oro<<endl;	
								}
					 }else{//si el numero es diferente a 1, esquivas su ataque y lo golpeas con doble de fuerza
					 	vida_jefe = vida_jefe - (2 * dpa);
					 		cout<<"  Has logrado esquivar su ataque, tu ataque ha duplicado su da�o, su vida";
					 		cout<<" ha bajado a ";
								if (vida_jefe > 0){//si aun tiene vida
									cout<<vida_jefe<<endl;
								}else{//si no tiene vida
									cout<<"0"<<endl;
								}		 		
					 }
		}else{//huir. No se puede, eres asesinado usando esta opcion
			system("cls");
				 srand(time(NULL));
				 aleatorio = rand()%(10-0+1)+0;//da un numero aleatorio (0-10)
					 	if(aleatorio != 0){//si no es 0 muertas un mensaje de muerte
							cout<<"  Has decidido escapar como una gallina, pero tus pies son m�s peque�os que los";
							cout<<" del \n  reptiliano. Te ha atrapado y devorado\n";
								presionar_continuar();
								endgame();//fin del juego
						}else{//si es exactamente  muestra un mensaje especial de muerte
						cout<<"  Robot - Parece que has decidido escapar, esto est� mal, los humanos no son";
						cout<<" cobardes,"<<endl<<"          ser�s eliminado\n";
							presionar_continuar();
							endgame();//fin del juego
						}
		}
}


void pelea_final(){//Sistema de pelea contra el jefe final (Nuevos dialogos)
	cout<<"  ===================================================================================="<<endl;
	cout<<"          [1 ATACAR]         [2 CUBRIRSE]        [3 ESQUIVAR]         [JAJAJA]        "<<endl;
	cout<<"          [        ]         [          ]        [  Y ATACAR]         [JAJAJA]        "<<endl;
	cout<<"  ===================================================================================="<<endl;
	cout<<"                                           ";cin>>continuar_pelea;
		if(continuar_pelea == 1){//atacar. Tu das un ataque y si enemigo aun conserva vida te ataca
			system("cls");
			vida_jefe = vida_jefe - dpa;//tu atacas primero
				cout<<"  Tu ataque ha hecho "<<dpa<<" puntos de da�o, ";
					if(vida_jefe>0){//si el enemigo aun tiene vida
					hp = hp - ataque_jefe; /*te ataca*/ muerte();/*revisa si aun tienes vda, si no muestra tu muerte*/
						cout<<"su vida restante es de "<<vida_jefe<<endl;
						cout<<"  Te ha atacado, tu vida ha bajado a "<<hp<<endl;
							if(oro <= 0){//si no tienes oro
								cout<<"  Su ataque no te ha quitado oro porque tienes "<<oro<<endl;
								cout<<"  THROPER - �ERES MUY LENTO!"<<endl;
							}else{//te quita oro
								oro = oro - 1;
								cout<<"  Su ataque te ha quitado 1 de oro, tu total de oro es de "<<oro<<endl;
								cout<<"  THROPER - �ERES MUY LENTO!"<<endl;	
							}
					}else{//si el enemigo ya no tiene vida despues de tu ataque
						cout<<"\n  THROPER - �NOOOOOOO IMPOSIBLE, NADIE VENCE A THROPER, NADIEEEE WRYYYYYYYY!"<<endl;
						cout<<"  Su vida restante es de 0, has acabado con el"<<endl;
						cout<<"  Tu vida restante es de "<<hp<<endl;//lo matas
					}
		}else if(continuar_pelea == 2){//cubirse. No puedes atacar, pero el da�o que te hacen se reduce 50%
			system("cls");
				hp = hp - (ataque_jefe * .5); /*te ataca*/ muerte();/*revisa si aun no has muerto*/
				cout<<"  Has decidido cubrirte, te ha atacado y su da�o fue reducido, tu vida ha bajado a "<<hp<<endl;
					if(oro <= 0){//si ya no tienes oro
								cout<<"  Su ataque no te ha quitado oro porque tienes "<<oro<<endl;
								cout<<"  �THROPER - �MUDA! �MUDA! �MUDA! �MUDA! �MUDA! �MUDAAAAAAAAAA!"<<endl;
					}else{//si tienes oro, te quita
						oro = oro - 1;
						cout<<"  Su ataque te ha quitado 1 de oro, tu total de oro es de "<<oro<<endl;
								cout<<"  �THROPER - �MUDA! �MUDA! �MUDA! �MUDA! �MUDA! �MUDAAAAAAAAAA!"<<endl;
					}
		}else{//esquivar y atacar. Aleatoriamente decide si esquivas o no su ataque. No exite opcion para huir
			system("cls");
				 srand(time(NULL));
				 aleatorio = rand()%(1-0+1)+0;//numero aleatorio
				 	if(aleatorio == 1){//si el numero es igual a 1, no esquivaste su ataque y te golpea dos veces mas fuerte
				 		hp = hp - (2*ataque_jefe); muerte();
				 			cout<<"  No has podido esquivar el ataque, te ha atacado en el doble de fuerza,"<<endl;
				 			cout<<"  tu vida ha bajado a "<<hp<<endl;
								if(oro <= 0){//si no tienes oro
								cout<<"  Su ataque no te ha quitado oro porque tienes "<<oro<<endl;
								cout<<"  �THROPER - �MUDA! �MUDA! �MUDA! �MUDA! �MUDA! �MUDAAAAAAAAAA!"<<endl;
								}else{//si tienes oro, te quita
									oro = oro - 1;
									cout<<"  Su ataque te ha quitado 1 de oro, tu total de oro es de "<<oro<<endl;
									cout<<"  �THROPER - �MUDA! �MUDA! �MUDA! �MUDA! �MUDA! �MUDAAAAAAAAAA!"<<endl;	
								}
					 }else{//si el numero es diferente a 1, esquivas su ataque y lo golpeas con doble de fuerza
					 	vida_jefe = vida_jefe - (2 * dpa);
					 		cout<<"  Has logrado esquivar su ataque, tu ataque ha duplicado su da�o, su vida";
					 		cout<<" ha bajado a ";
								if (vida_jefe > 0){//si aun tiene vida
									cout<<vida_jefe<<endl;
									cout<<"  Tripulante 7 - �Ora! �Ora! �Ora! �Ora �Ora!"<<endl;
									cout<<"  THROPER - WRYYYYYYYY"<<endl;
								}else{//si no tiene vida
									cout<<"0"<<endl;
									cout<<"  THROPER - �NOOOOOOO IMPOSIBLE, NADIE VENCE A THROPER, NADIEEEE WRYYYYYYYY!"<<endl;
								}		 		
					 }
		}
}


void presionar_continuar(){//opcion que funcione como pausa para el usuario
	cout<<"  ===================================================================================="<<endl;
	cout<<"                               Presione 1 para continuar"<<endl;
	cout<<"                                           ";
	do{//entra en un bucle
		cin>>continuar_1;//pide un numero
	}while(continuar_1 != 1);//sale del bucle hasta que el numero sea 1
			continuar_1 = 10;
	system("cls");
 	cout<<"  ===================================================================================="<<endl;
}


void datos_Partida(){//datos y estadisticas acumuladas
	system("cls");
		cout<<"  ===================================================================================="<<endl;
		cout<<"                               BIENVENIDO A COLOMBUS 127                              "<<endl;
		cout<<"  ===================================================================================="<<endl;
		cout<<"  Las estad�sticas y las estrellas est�n a tu favor. Usa tu sabidur�a"<<endl<<endl;
		cout<<"  Tu vida actual es de: "<<hp<<endl;
		cout<<"  Tu oro actual es de: "<<oro<<endl;
		cout<<"  Tu da�o por ataque actual es de: ";cout<<dpa<<endl;
		cout<<"  El nivel en el que actualmente estas es el: "<<lvl<<endl;
	presionar_continuar();//ir a pausa
	parte_Nivel();//una vez que se sabe el nivel se llama a la funcion y te direcciona a ese nivel
}


void menuNivel(){//menu al final de un nivel
	system("cls");
	cout<<"  ===================================================================================="<<endl;
	cout<<"  Que accion desea hacer?"<<endl<<endl;
	cout<<"  [1 GUARDAR PARTIDA]  [2 CARGAR PARTIDA]  [3 GUARDAR Y SALIR]  [4 AVANZAR SIN GUARDAR]"<<endl;
	cout<<"                                     [0 SALIR]"<<endl;
	cout<<"  ===================================================================================="<<endl;
	cout<<"                                           ";cin>>continuar_1;
		if(continuar_1 == 1){//guardar
			lvl = lvl + 1; //suma un nivel para empezar desde el siguente nivel
			guardarPartida_h(); 
			datos_Partida(); 
		}else if(continuar_1 == 2){//cargar partida
			cargarPartida_h();
			datos_Partida();
		}else if(continuar_1 == 3){//guardar y salir
			lvl = lvl + 1; //suma un nivel para empezar desde el siguente nivel
			guardarPartida_h();
			presionar_continuar();
			endgame();//fin
		}else if(continuar_1 == 4){//avanzar sin guardar
			lvl = lvl + 1;//suma un nivel
			datos_Partida();//avanza
		}else{//salir sin guardar
			endgame();//termina el juego y no guarda
		}
}


void muerte(){
	if(hp <= 0){//si la vida del personaje principal es menor o igual a 0
		system("cls");
		cout<<"  ===================================================================================="<<endl;
		cout<<"                                      HAS MUERTO"<<endl;
	presionar_continuar();endgame(); //fin del juego
	}
}


void endgame(){//fin del juego
	system("cls");
	cout<<"  ===================================================================================="<<endl;
	cout<<"                                          END                                         "<<endl;
	cout<<"                                          GAME                                        "<<endl;
	cout<<"  ===================================================================================="<<endl;
	cout<<"                              Gracias por jugar mi juego c:                           "<<endl;
	cout<<"  ===================================================================================="<<endl;
	exit(119);
}


void mapa(){
	cout<<"  ===================================================================================="<<endl;
	cout<<"                             MAPA DE LA NAVE 'LA FLECHA'                              "<<endl;
	cout<<"  ===================================================================================="<<endl;
	cout<<"                                                                                      "<<endl;
	cout<<"                            ***************                                           "<<endl;
	cout<<"                           *   Unidad de   *                                          "<<endl;
	cout<<"  ******************       * Investigaci�n *                                          "<<endl;
	cout<<"  **               **      *    Colombus   *                       *********          "<<endl;
	cout<<"  **               **      *               *    ************      *         **        "<<endl;
	cout<<"  **               **      ******     ******    *          *     *            **      "<<endl;
	cout<<"  **               **           *     *         *  Modulo  *    *               **    "<<endl;
	cout<<"  **               **************     ***********    de    *****     Puerto       **  "<<endl;
	cout<<"  ** Habitaciones                                 Servicio             de           **"<<endl;
	cout<<"  **                                             Sistem�tico         Control        **"<<endl;
	cout<<"  **               **************     ***********          *****                  **  "<<endl;
	cout<<"  **               **           *     *         *          *    *               **    "<<endl;
	cout<<"  **               **       *****     *****     *          *     *            **      "<<endl;
	cout<<"  **               **       * Laboratorio *     ************      *         **        "<<endl;
	cout<<"  **               **       *   Century   *                        *********          "<<endl;
	cout<<"  ******************        *             *                                           "<<endl;
	cout<<"                            ***************                                           "<<endl;
	cout<<"                                                                                      "<<endl;
	cout<<"  ===================================================================================="<<endl;
	cout<<"     Atenci�n, todo el personal debe permanecer junto, por ninguna raz�n separarse    "<<endl;
}


void reptiliano_1(){
	cout<<"  ===================================================================================="<<endl;
	cout<<"                                   _.-_                                               "<<endl;
	cout<<"                               __.'  o ''-.                                           "<<endl;
	cout<<"                      ___----'''        ,,,'                                          "<<endl;
	cout<<"                 __--'             _-_ ^^;                                            "<<endl;
	cout<<"         ____--''  ___         _-)'   `''                                             "<<endl;
	cout<<"  ..--===-------'''   '(   __-' ' ,}                                                  "<<endl; 
	cout<<"                      .'_/')                                                          "<<endl;
	cout<<"                    .'/'  `)`._c                                                      "<<endl;
	cout<<"                    '-_c                                                              "<<endl;
}


void reptiliano_2(){
	cout<<"  ===================================================================================="<<endl;
	cout<<"                                                                  /           /       "<<endl;    
	cout<<"                                                                 /' .,,,,  ./         "<<endl;   
	cout<<"                                                                /';'     ,/           "<<endl; 
	cout<<"                                                               / /   ,,//,`'`         "<<endl; 
	cout<<"                                                              ( ,, '_,  ,,,' ``       "<<endl;
	cout<<"                                                              |    /@  ,,, ;'' `      "<<endl;
	cout<<"                                                             /    .   ,''/' `,``      "<<endl;
	cout<<"                                                            /   .     ./, `,, ` ;     "<<endl;
	cout<<"                                                         ,./  .   ,-,',` ,,/''),'     "<<endl;
	cout<<"                                                        |   /; ./,,'`,,'' |   |       "<<endl;
	cout<<"                                                        |     /   ','    /    |       "<<endl;
	cout<<"                                                        |___/'   '     |     |        "<<endl;
	cout<<"                                                           `,,'  |      /     `|      "<<endl;
	cout<<"                                                                 /      |             "<<endl;
	cout<<"                                                               '       (              "<<endl;
}


void dio(){
	cout<<"  ===================================================================================="<<endl;
	 cout<<"                                     ,-.                                "<<endl;
	printf("                ___,---.__          /'|`%c          __,---,___          \n",92);
	printf("             ,-'    %c`    `-.____,-'  |  `-.____,-'    //    `-.       \n",92);
	printf("           ,'        |           ~'%c     /`~           |        `.      \n",92);
	printf("          /      ___//              `. ,'          ,  , %c___      %c    \n",92,92);
	printf("         |    ,-'   `-.__   _         |        ,    __,-'   `-.    |    \n");
	printf("         |   /          /%c_  `   .    |    ,      _/%c          %c   |   \n",92,92,92);
	printf("         %c  |           %c %c`-.___ %c   |   / ___,-'/ /           |  /   \n",92,92,92,92);
	printf("          %c  %c           | `._   `%c%c  |  //'   _,' |           /  /      \n",92,92,92,92);
	printf("           `-.%c         /'  _ `---'' , . ``---' _  `%c         /,-'     \n",92,92);
	printf("              ``       /     %c    ,='/ %c`=.    /     %c       ''         \n",92,92,92); 
	printf("                      |__   /|%c_,--.,-.--,--._/|%c   __|                  \n",92,92);
	printf("                      /  `./  %c%c`%c |  |  | /,//' %c,'  %c                  \n",92,92,92,92,92);
	printf("                     /   /     ||--+--|--+-/-|     %c   %c                 \n",92,92);
	printf("                    |   |     /'%c_%c_%c | /_/_/`%c     |   |                \n",92,92,92,92);
	printf("                     %c   %c__, %c_     `~'     _/ .__/   /            \n",92,92,92);
	cout<<"                      `-._,-'   `-._______,-'   `-._,-'	"<<endl;
}

///////////////////////////////////					MODO DIO				///////////////////////////////////
void nuevaPartida_d(){
	ofstream archivoPP;
	archivoPP.open("DatosPerP-ModoDIO.txt",ios::out);//abrir archivo para datos del personaje principal, distinto modo historia
	
	if(!archivoPP.fail()){
		archivoPP<<"hp:100."<<endl;//vida
		archivoPP<<"or:0."<<endl; //monedas
		archivoPP<<"dpa:10."<<endl; //da�o por ataque 
	}else{
		cout<<"Imposible realizar esta operaci�n";
		exit(1);
	}
	cargarPartida_d();	
}


void cargarPartida_d(){
	ifstream archivoPP;
	string datos;
	bool hp_flag = false, oro_flag = false, dpa_flag = false;
	
	archivoPP.open("DatosPerP-ModoDIO.txt",ios::in);//en un archivo distinto al del modo historia
		if(!archivoPP.fail()){//si existe
			while(!archivoPP.eof()){
			getline(archivoPP,datos);
				for(int i = 0; i < datos.size(); i++){
					switch(datos[i]){
						case 'h': //leer para hp (vida)
							for(int i = 0; i < datos.size(); i++){
								if(datos[i] == ':'){//cuando lea un :
									hp_flag = true;
								}else{
									if(hp_flag == true){
										if(datos[i] != '.'){//guardar hasta encontrar un .
											s_hp = s_hp + datos[i];
										}
									}
								}
							}break;
						case 'o'://leer para or (oro)
							for(int i = 0; i < datos.size(); i++){
								if(datos[i] == ':'){//cuando lea un :
									oro_flag = true;
								}else{
									if(oro_flag == true){
										if(datos[i] != '.'){//guardar hasta encontrar un .
											s_oro = s_oro + datos[i];
										}
									}
								}
							}break;
						case 'd': //leer para dpa (da�o por ataque)
							for(int i = 0; i < datos.size(); i++){
								if(datos[i] == ':'){//cuando lea un :
									dpa_flag = true;
								}else{
									if(dpa_flag == true){
										if(datos[i] != '.'){//guardar hasta encontrar un .
											s_dpa = s_dpa + datos[i];
										}
									}
								}
							}break;
					}
				}
			}
		}else{//si falla
			cout<<"Imposible realizar esta operaci�n";
			exit (2);
		}
	hp = atoi(s_hp.c_str());//cambiar string a variables int para poderlas manejar en el archivo
	oro = atoi(s_oro.c_str());
	dpa = atoi(s_dpa.c_str());
	s_hp.erase(); s_oro.erase(); s_dpa.erase(); s_lvl.erase();	
}


void guardarPartida_d(){
	ofstream archivoPP;
	archivoPP.open("DatosPerP-ModoDIO.txt",ios::out);//abrir archivo para datos del personaje principal
	
	if(!archivoPP.fail()){
		archivoPP<<"hp:"<<hp<<"."<<endl;//vida
		archivoPP<<"or:"<<oro<<"."<<endl; //monedas
		archivoPP<<"dpa:"<<dpa<<"."<<endl; //da�o por ataque 
	}else{//no se encuentra el archivio
		cout<<"Imposible realizar esta operacion";
		exit(1);
	}
}

void menu_dio(){//Menu de accion para el usuario
	system("cls");
	cout<<"  ===================================================================================="<<endl;
	cout<<"                               BIENVENIDO A COLOMBUS 127                              "<<endl;
	cout<<"  ===================================================================================="<<endl;
	cout<<"                     Por favor, ingrese la acci�n que desea realizar,                 "<<endl;
	cout<<"  [1 GANAR ORO]         [2 PERDER ORO]         [3 GANAR VIDA]         [4 PERDER VIDA]"<<endl;
	cout<<"             [5 GANAR DA�O POR ATAQUE]           [6 PERDER DA�O POR ATAQUE]          "<<endl;
	cout<<"  [7 GUARDAR PARTIDA]      [8 CARGAR PARTIDA]      [9 GUARDAR Y SALIR]      [0 SALIR]"<<endl;
	cout<<"                                           ";cin>>continuar_1;
		if(continuar_1  == 1){
			oro = oro + 1;//gana 1 de oro
			cout<<"  Tu oro ha subido un punto"<<endl;
		}else if(continuar_1  == 2){
			if(oro > 0){//siempre y cuando tenga oro
				oro = oro - 1;//pierde 1 de oro
				cout<<"  Tu oro se ha reducido un punto"<<endl;
			}else{//tu oro es 0
				cout<<"  No tienes oro suficiente"<<endl;
			}
		}else if(continuar_1  == 3){
			if(hp < 100){//siempre y cuando su vida sea menos de 100
				hp = hp + 1;//ganar 1 de vida
				cout<<"  Tu vida ha subido un punto"<<endl;
			}else{
				cout<<"  Tu vida esta completa, no puedes aumentarla m�s"<<endl;
			}
		}else if(continuar_1  == 4){
			hp = hp - 1;//perder 1 de vida			
				if(hp > 0){//cuando su vida sea mayor a 0
					cout<<"  Tu vida ha bajado un punto"<<endl;
				}else{
					muerte();
				}
		}else if(continuar_1  == 5){
			dpa = dpa + 1;//ganar da�o por ataque
			cout<<"  Tu da�o por ataque ha subido un punto"<<endl;
		}else if(continuar_1  == 6){
			if(dpa > 0){//siempre y cuando tu da�o sea mayor a 0
				dpa = dpa - 1;//perder 1 de da�o
				cout<<"  Tu da�o por ataque ha bajado un punto"<<endl;
			}else{
				cout<<"  Imposible, tu da�o no puede ser menor a 1"<<endl;
			}
		}else if(continuar_1  == 7){
			guardarPartida_d();//guardar la partida
		}else if(continuar_1  == 8){
			cargarPartida_d();
		}else if(continuar_1  == 9){
			guardarPartida_d();//guarda partida
			presionar_continuar();//espera confirmacion usuario
			endgame();//termina proceso
		}else{
			endgame();//terminar juego
		}
	resultado_Datos();
}

void resultado_Datos(){
	cout<<"  ===================================================================================="<<endl;
	cout<<"                           Tus estadisticas han cambiado"<<endl;
	cout<<"  ===================================================================================="<<endl;
	cout<<"  Tu vida actual es de: "<<hp<<" puntos"<<endl;
	cout<<"  Tu oro actual es de: "<<oro<<endl;
	cout<<"  Tu da�o por ataque actual es de: "<<dpa<<" puntos"<<endl;
	presionar_continuar();
	menu_dio();
}

import java.io.IOException;
import java.util.Scanner;

public class Juego {
	public static int pos1=0, pos2=0;
	
	public static void main(String[] args) throws IOException {
		int aprobados=0, reprobados=0;
		boolean flag=true;
		Mano Player= new Mano();
		Mazo Universitario = new Mazo();
		Mazo Carrera = new Mazo();
		Tablero tablero= new Tablero();
		System.out.println("hola");
		initEstudios(Universitario);
		initCarrera(Carrera);
		Carta car;
		int pos1=0, pos2=0;
		Scanner inputMain=new Scanner(System.in);
		while(flag) {
			while(Player.getSize()<6) {
				Player.anadirCarta(Universitario.draw());
			}
			for(int i=0; i<2;i++) {
				tablero.Semestre.add((Ramo)Carrera.draw());
			}
			
			while(tablero.horasDisponibles>0 && Player.getSize()>0) {
				System.out.println("WidePeepoHappy Ramos Aprobados : "+ aprobados);
				System.out.println("WidePeepoSad   Ramos Reprobados : " + reprobados);
				Player.mostrarMano();
				tablero.mostrarTablero();
				System.out.println(">>>Escoge el numero de la Carta a jugar(8 para Saltar Turno): ");
				pos1=inputMain.nextInt();
				if(pos1==8) {
					break;
				}
				try {
					car=Player.seleccionarCarta(pos1-1);
					if(car instanceof Estudio) {
						System.out.println(">>>En que Ramo desea jugar, para deseleccionar presione 4 : ");
						pos2=inputMain.nextInt();
						System.out.println(pos2);
						switch (pos2) {
							case 1:
								tablero.jugarEstudio((Estudio)car, pos2-1);
								break;
							case 2:
								tablero.jugarEstudio((Estudio)car, pos2-1);
								break;
							case 4:
								Player.anadirCarta(car);
							default:
								System.out.println("Numero Invalido");
						}
					}
					else if(car instanceof Evento) {
						switch(((Evento)car).efect) {
							case RAV:
								System.out.println("A que Ramo(1|2)?");
								pos2=inputMain.nextInt();
								((Evento) car).aplicarEvento(tablero, Carrera, pos2);
								break;
							case Buff:
								System.out.println("A que Area:\n1. Matematicas\n2. Humanista\n3. Informatica)?");
								((Evento) car).aplicarEvento(tablero, Carrera, pos2);
							case CambioCoordinacion:
								System.out.println("A que Ramo(1|2)?");
								pos2=inputMain.nextInt();
								((Evento) car).aplicarEvento(tablero, Carrera, pos2);
								break;
							default:
								break;
						}
					}
				}catch(Exception e) {
					System.out.println("Carta Invalida");
				}
			}
			for(int i=0; i<tablero.Semestre.size();i++) {
				if(tablero.Semestre.get(i).getNota()>=55) {
					aprobados++;
				}
				else {
					reprobados++;
				}
			}
			if(aprobados==4) {
				System.out.println("ʕ•ᴥ•ʔʕ•ᴥ•ʔ     GANASTE     ʕ•ᴥ•ʔʕ•ᴥ•ʔ");
				break;
			}
			else if(reprobados==2) {
				System.out.println(">>>>Fuiste consumido por el PRESTIGIO<<<<");
				break;
			}
			tablero.clearTablero();
			Player.clearMano();
			
		}
		inputMain.close();
	}
	
	public static void initEstudios(Mazo Uni) {

		//Humanistas
		Estudio cart= new Estudio();
		cart.iniciarEstudio(Rareza.Comunes, Area.Humanista, "Por fin te pones a estudiar", "PogU comenzaste a estudiar PogU");
		Uni.putBack(cart);
		Uni.putBack(cart);
		Uni.putBack(cart);
		
		Estudio cart2= new Estudio();
		cart2.iniciarEstudio(Rareza.Raras, Area.Humanista, "Motivational Lizard version Humanista", "https://www.youtube.com/watch?v=kGOQfLFzJj8");
		Uni.putBack(cart2);
		cart2= new Estudio();
		cart2.iniciarEstudio(Rareza.Raras, Area.Humanista, "WidePeepoSad", "Te bendice WidePeepoSad lo que hace que estudies mas eficientemente");
		Uni.putBack(cart2);
		
		Estudio cart3= new Estudio();
		cart3.iniciarEstudio(Rareza.Epicas, Area.Humanista, "Maquina del Tiempo", "Pudiste viajar al pasado para saber que paso en la historia");
		Uni.putBack(cart3);
		
		//Matematicas
		Estudio cart4= new Estudio();
		cart4.iniciarEstudio(Rareza.Comunes, Area.Matematica, "Sesion Grupal", "Tu y tus amigos se pudieron mandar su maraton para rushear la materia");
		Uni.putBack(cart4);
		Uni.putBack(cart4);
		Uni.putBack(cart4);
		
		Estudio cart5= new Estudio();
		cart5.iniciarEstudio(Rareza.Raras, Area.Matematica, "Wolfram", "Symbolab pero es mas complicado pero mas util");
		Uni.putBack(cart5);
		cart5= new Estudio();
		cart5.iniciarEstudio(Rareza.Raras, Area.Matematica, "Symbolab", "Symbolab te ayuda a aprender a hacer TODO!");
		Uni.putBack(cart5);
		//Mirar El video si te sientes desmotivado
		Estudio cart6= new Estudio();
		cart6.iniciarEstudio(Rareza.Epicas, Area.Matematica, "Motivational Lizard V2 matematicas Edition", "https://www.youtube.com/watch?v=xvvuNHMHyGc");
		Uni.putBack(cart6);
		
		//Informatica
		Estudio cart7= new Estudio();
		cart7.iniciarEstudio(Rareza.Comunes, Area.Informatica, "Modo Oscuro", "Modo Oscuro Gang");
		Uni.putBack(cart7);
		cart7= new Estudio();
		cart7.iniciarEstudio(Rareza.Comunes, Area.Informatica, "se te rompio la tablet", "Ya no puedes jugar OSU!, tienes mas tiempo libre");
		Uni.putBack(cart7);
		cart7= new Estudio();
		cart7.iniciarEstudio(Rareza.Comunes, Area.Informatica, "2 Monitores", "Ahora puedes programar y mirar videos de TuTubo(no quiero que me den un Strike)");
		Uni.putBack(cart7);
		cart7= new Estudio();
		cart7.iniciarEstudio(Rareza.Comunes, Area.Informatica, "Teclado Mecanico", "Con tus nuevos Cherry Blue escribir se siente maravilloso");
		Uni.putBack(cart7);
		
		Estudio cart8= new Estudio();
		cart8.iniciarEstudio(Rareza.Raras, Area.Informatica,"Resumenes de Gabi", "@resumenesdegabi");
		Uni.putBack(cart8);
		cart8= new Estudio();
		cart8.iniciarEstudio(Rareza.Raras, Area.Informatica,"SoloLearn", "Pudiste Aprender un Lenguaje de Programacion en 2 Horas");
		Uni.putBack(cart8);
		cart8= new Estudio();
		cart8.iniciarEstudio(Rareza.Raras, Area.Informatica,"Stack Overflow", "No hablo del foro, te salio el error al Programar y aprendiste de tu error");
		Uni.putBack(cart8);
		
		Estudio cart9= new Estudio();
		cart9.iniciarEstudio(Rareza.Epicas, Area.Informatica,"Perdiste completamente tu Sanidad", "https://www.youtube.com/watch?v=c_jomXhjUjI");
		Uni.putBack(cart9);
		
		Evento carta=new Evento();
		carta.initEvento(efecto.Buff, "Notas del Parche","Buffeo a Cierta Area(Matematicas, Informatica o Humanista)");
		carta=new Evento();
		Uni.putBack(cart8);
		
		carta.initEvento(efecto.RAV, "Boton de Panico","https://www.youtube.com/watch?v=AZY8P3eVQ94");
		Uni.putBack(carta);
		Uni.putBack(carta);
		
		carta=new Evento();
		carta.initEvento(efecto.CambioCoordinacion, "Nueva Coordinacion","Cambio el Coordinador del ramo");
		Uni.putBack(carta);
		Uni.putBack(carta);
		Uni.shuffle();
		
	}
	
	public static void initCarrera(Mazo Carrera) {
		Ramo ram1=new Ramo();
		ram1.initRamo(Area.Humanista, "Humanista101", "Santa Maria no deja jugar hearthstone");
		Carrera.putBack(ram1);
		
		ram1=new Ramo();
		ram1.initRamo(Area.Humanista, "Humanista102", "Funa Tapia");
		Carrera.putBack(ram1);
		
		ram1=new Ramo();
		ram1.initRamo(Area.Matematica, "Mate021", "no te quedes dormido en clases");
		Carrera.putBack(ram1);
		
		ram1=new Ramo();
		ram1.initRamo(Area.Matematica, "Mate022", "no te olvides de la C");
		Carrera.putBack(ram1);
		
		ram1=new Ramo();
		ram1.initRamo(Area.Matematica, "Mate023", "no se entiende, se pasa");
		Carrera.putBack(ram1);
		
		ram1=new Ramo();
		ram1.initRamo(Area.Matematica, "Mate024", "no entiendo lo que esta pasando");
		Carrera.putBack(ram1);
		
		ram1=new Ramo();
		ram1.initRamo(Area.Informatica, "IWI131", "Grande F. Meza");
		Carrera.putBack(ram1);
		
		ram1=new Ramo();
		ram1.initRamo(Area.Informatica, "Intro ingenieria", "Hagalo Usted mismo");
		Carrera.putBack(ram1);
		
		ram1=new Ramo();
		ram1.initRamo(Area.Informatica, "INF-134", "Mal Uso del TDA -15 puntos");
		Carrera.putBack(ram1);
		
		ram1=new Ramo();
		ram1.initRamo(Area.Informatica, "Estructuras Discretas", "Grande la musica de Deuman");
		Carrera.putBack(ram1);
		
		Carrera.shuffle();
		
	}
}

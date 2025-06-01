#include <stdio.h>
#include <string.h>

#define MAX_TXT 80
#define MAX_ACTORS 100
#define MAX_MOVIES 100

typedef struct{
    int id;
    char name[MAX_TXT];
}Actor;

typedef struct{
    char title[MAX_TXT];
    int year;
    char director[MAX_TXT];
    int actors_ids[MAX_ACTORS];
    int nb_actors;
}Movie;

int addActors(Actor actors[MAX_ACTORS]) {
    //TODO: Solicitar el id y nombre del actor y añadirlo al arreglo. Habrá que preguntarle al usuario si se desea
    // añadir más actores al arreglo, en caso contrario volver al menú principal. Se devuelve la cantidad de actores entrados al arreglo.
}

int addMovies(Movie movies[MAX_MOVIES]) {
    //TODO: Solicitar el título, año de lanzamiento y director de la película y añadirlo al arreglo. Tened en cuenta que
    // también se ha de solicitar el id de los actores que participen en dicha película. Se deberá en todo momento, preguntar si se desean añadir nuevos actores y/o películas.
    // Se devuelve la cantidad de películas entrados al arreglo.
}

int getIdByName(Actor actors[], int num_actors, char name[]){
    //TODO: Dado un nombre entrado por parámetro, buscar y devolver el id del actor correspondiente al mismo.
}

void getNameById(Actor actors[], int num_actors, char name[], int id){
    //TODO: Dado un id entrado por parámetro, buscar el nombre del actor correspondiente al mismo. La variable name, es donde se depositará el nombre del actor encontrado.
}

void showMoviesByActor(Movie movies[], int num_movies, Actor actors[], int num_actors) {
    //TODO: Se ha de solicitar el nombre del actor y mostrar el listado de películas que son protegonizadas por el mismo.
}

void reportActorsByDirector(Movie movies[], int num_movies, Actor actors[], int num_actors) {
    // TODO: Se ha de solicitar el nombre del director y crear un fichero de texto llamado "reportABD.txt" con el nombre
    //  de los actores que participen en las películas dirigidas por dicho director
}

int deleteMovieByYear(Movie movies[], int num_movies) {
    //TODO: Se ha de solicitar el año de la película que se desea eliminar, encontrarlas y quitarlas del arreglo
}

void reportCurrentMovies(Movie movies[], int num_movies) {
    // TODO: Se ha de crear un fichero de binario llamado "reportCM.bin" con las pelñiculas que solo pertenezcan al año actual
}

int main() {
    Actor actors[MAX_ACTORS];
    Movie movies[MAX_MOVIES];
    int num_actors = 0, num_movies = 0;
    int option=0;

    do {
        printf("---- MENU ----\n");
        printf("1. Enter actors \n");
        printf("2. Enter movies \n");
        printf("3. Show movies by actor \n");
        printf("4. Report actors who have worked with x director... \n");
        printf("5. Delete movies by year \n");
        printf("6. Report current movies... \n");
        printf("7. Exit \n");
        printf("Enter option: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                num_actors = addActors(actors);
                break;
            case 2:
                num_movies = addMovies(movies);
                break;
            case 3:
                showMoviesByActor(movies, num_movies, actors, num_actors);
                break;
            case 4:
                reportActorsByDirector(movies, num_movies, actors, num_actors);
                break;
            case 5:
                num_movies = deleteMovieByYear(movies, num_movies);
                break;
            case 6:
                reportCurrentMovies(movies, num_movies);
                break;
            case 7:
                printf("Program closing...\n");
                break;
        }
        printf("\n");
    }while(option!=7);

    return 0;
}

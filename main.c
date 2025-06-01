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
    int num_actors = 0;
    char continue_adding = 'y';
    
    while (continue_adding == 'y' || continue_adding == 'Y') {
        if (num_actors < MAX_ACTORS) {
            printf("Enter actor ID: ");
            scanf("%d", &actors[num_actors].id);
            
            printf("Enter actor name: ");
            scanf("%s", actors[num_actors].name);
            
            num_actors++;
            
            printf("Do you want to add another actor? (y/n): ");
            scanf(" %c", &continue_adding);
        } else {
            printf("Maximum number of actors reached!\n");
            continue_adding = 'n';
        }
    }
    
    return num_actors;
}

int addMovies(Movie movies[MAX_MOVIES]) {
    int num_movies = 0;
    char continue_adding = 'y';
    
    while (continue_adding == 'y' || continue_adding == 'Y') {
        if (num_movies < MAX_MOVIES) {
            printf("Enter movie title: ");
            scanf("%s", movies[num_movies].title);
            
            printf("Enter movie year: ");
            scanf("%d", &movies[num_movies].year);
            
            printf("Enter director name: ");
            scanf("%s", movies[num_movies].director);
            
            movies[num_movies].nb_actors = 0;
            char add_actor = 'y';
            
            while ((add_actor == 'y' || add_actor == 'Y') && movies[num_movies].nb_actors < MAX_ACTORS) {
                printf("Enter actor ID: ");
                scanf("%d", &movies[num_movies].actors_ids[movies[num_movies].nb_actors]);
                movies[num_movies].nb_actors++;
                
                printf("Add another actor? (y/n): ");
                scanf(" %c", &add_actor);
            }
            
            num_movies++;
            
            printf("Add another movie? (y/n): ");
            scanf(" %c", &continue_adding);
        } else {
            printf("Maximum number of movies reached!\n");
            continue_adding = 'n';
        }
    }
    
    return num_movies;
}

int getIdByName(Actor actors[], int num_actors, char name[]){
    int found_id = -1;
    int i = 0;
    
    while (i < num_actors && found_id == -1) {
        if (strcmp(actors[i].name, name) == 0) {
            found_id = actors[i].id;
        }
        i++;
    }
    
    return found_id;
}

void getNameById(Actor actors[], int num_actors, char name[], int id){
    int i = 0;
    int found = 0;
    
    while (i < num_actors && found == 0) {
        if (actors[i].id == id) {
            strcpy(name, actors[i].name);
            found = 1;
        }
        i++;
    }
    
    if (found == 0) {
        strcpy(name, "Actor not found");
    }
}

void showMoviesByActor(Movie movies[], int num_movies, Actor actors[], int num_actors) {
    char actor_name[MAX_TXT];
    int actor_id = -1;
    int found = 0;
    int i = 0;
    
    printf("Enter actor name: ");
    scanf("%s", actor_name);
    
    while (i < num_actors && found == 0) {
        if (strcmp(actors[i].name, actor_name) == 0) {
            actor_id = actors[i].id;
            found = 1;
        }
        i++;
    }
    
    if (found == 1) {
        printf("\nMovies starring %s:\n", actor_name);
        for (i = 0; i < num_movies; i++) {
            for (int j = 0; j < movies[i].nb_actors; j++) {
                if (movies[i].actors_ids[j] == actor_id) {
                    printf("- %s (%d) directed by %s\n", 
                        movies[i].title, 
                        movies[i].year, 
                        movies[i].director);
                }
            }
        }
    } else {
        printf("Actor not found!\n");
    }
}

void reportActorsByDirector(Movie movies[], int num_movies, Actor actors[], int num_actors) {
    char director_name[MAX_TXT];
    FILE *file;
    int actor_ids[MAX_ACTORS];
    int num_unique_actors = 0;
    int i, j, k;
    int is_duplicate;
    
    printf("Enter director name: ");
    scanf("%s", director_name);
    
    file = fopen("reportABD.txt", "w");
    if (file != NULL) {
        for (i = 0; i < num_movies; i++) {
            if (strcmp(movies[i].director, director_name) == 0) {
                for (j = 0; j < movies[i].nb_actors; j++) {
                    is_duplicate = 0;
                    for (k = 0; k < num_unique_actors; k++) {
                        if (actor_ids[k] == movies[i].actors_ids[j]) {
                            is_duplicate = 1;
                        }
                    }
                    if (is_duplicate == 0) {
                        actor_ids[num_unique_actors] = movies[i].actors_ids[j];
                        num_unique_actors++;
                    }
                }
            }
        }
        
        fprintf(file, "Actors who worked with director %s:\n", director_name);
        for (i = 0; i < num_unique_actors; i++) {
            for (j = 0; j < num_actors; j++) {
                if (actors[j].id == actor_ids[i]) {
                    fprintf(file, "- %s\n", actors[j].name);
                }
            }
        }
        
        fclose(file);
        printf("Report created successfully in reportABD.txt\n");
    } else {
        printf("Error creating report file!\n");
    }
}

int deleteMovieByYear(Movie movies[], int num_movies) {
    int year;
    int i = 0;
    
    printf("Enter year to delete movies from: ");
    scanf("%d", &year);
    
    while (i < num_movies) {
        if (movies[i].year == year) {
            for (int j = i; j < num_movies - 1; j++) {
                movies[j] = movies[j + 1];
            }
            num_movies--;
        } else {
            i++;
        }
    }
    
    printf("Deleted all movies from year %d\n", year);
    return num_movies;
}

void reportCurrentMovies(Movie movies[], int num_movies) {
    FILE *file;
    int current_year = 2024;
    int movies_written = 0;
    int i;
    
    file = fopen("reportCM.bin", "wb");
    if (file != NULL) {
        for (i = 0; i < num_movies; i++) {
            if (movies[i].year == current_year) {
                movies_written++;
            }
        }
        
        fwrite(&movies_written, sizeof(int), 1, file);
        
        for (i = 0; i < num_movies; i++) {
            if (movies[i].year == current_year) {
                fwrite(&movies[i], sizeof(Movie), 1, file);
            }
        }
        
        fclose(file);
        printf("Report created successfully in reportCM.bin\n");
    } else {
        printf("Error creating report file!\n");
    }
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

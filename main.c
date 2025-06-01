#include <stdio.h>
#include <string.h>
#include <time.h>

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
            
            printf("Enter release year: ");
            scanf("%d", &movies[num_movies].year);
            
            printf("Enter director name: ");
            scanf("%s", movies[num_movies].director);
            
            // Initialize number of actors for this movie
            movies[num_movies].nb_actors = 0;
            
            // Add actors to the movie
            char add_actor = 'y';
            while ((add_actor == 'y' || add_actor == 'Y') && movies[num_movies].nb_actors < MAX_ACTORS) {
                int actor_id;
                printf("Enter actor ID: ");
                scanf("%d", &actor_id);
                
                movies[num_movies].actors_ids[movies[num_movies].nb_actors] = actor_id;
                movies[num_movies].nb_actors++;
                
                printf("Do you want to add another actor to this movie? (y/n): ");
                scanf(" %c", &add_actor);
            }
            
            num_movies++;
            
            printf("Do you want to add another movie? (y/n): ");
            scanf(" %c", &continue_adding);
        } else {
            printf("Maximum number of movies reached!\n");
            continue_adding = 'n';
        }
    }
    
    return num_movies;
}

int getIdByName(Actor actors[], int num_actors, char name[]) {
    for (int i = 0; i < num_actors; i++) {
        if (strcmp(actors[i].name, name) == 0) {
            return actors[i].id;
        }
    }
    return -1;  // Return -1 if no actor with the given name is found
}

void getNameById(Actor actors[], int num_actors, char name[], int id) {
    name[0] = '\0';  // Initialize name as empty string
    for (int i = 0; i < num_actors; i++) {
        if (actors[i].id == id) {
            strcpy(name, actors[i].name);
        }
    }
}

void showMoviesByActor(Movie movies[], int num_movies, Actor actors[], int num_actors) {
    char actor_name[MAX_TXT];
    printf("Enter actor name: ");
    scanf("%s", actor_name);
    
    int actor_id = getIdByName(actors, num_actors, actor_name);
    
    if (actor_id == -1) {
        printf("Actor not found.\n");
    } else {
        printf("Movies featuring %s:\n", actor_name);
        for (int i = 0; i < num_movies; i++) {
            for (int j = 0; j < movies[i].nb_actors; j++) {
                if (movies[i].actors_ids[j] == actor_id) {
                    printf("- %s (%d) directed by %s\n", 
                           movies[i].title, 
                           movies[i].year, 
                           movies[i].director);
                }
            }
        }
    }
}

void reportActorsByDirector(Movie movies[], int num_movies, Actor actors[], int num_actors) {
    char director_name[MAX_TXT];
    printf("Enter director name: ");
    scanf("%s", director_name);
    
    FILE *file = fopen("reportABD.txt", "w");
    if (file == NULL) {
        printf("Error creating report file.\n");
    } else {
        fprintf(file, "Actors who worked with director %s:\n", director_name);
        
        for (int i = 0; i < num_movies; i++) {
            if (strcmp(movies[i].director, director_name) == 0) {
                for (int j = 0; j < movies[i].nb_actors; j++) {
                    char actor_name[MAX_TXT];
                    getNameById(actors, num_actors, actor_name, movies[i].actors_ids[j]);
                    fprintf(file, "- %s\n", actor_name);
                }
            }
        }
        
        fclose(file);
        printf("Report created successfully in reportABD.txt\n");
    }
}

int deleteMovieByYear(Movie movies[], int num_movies) {
    int year;
    printf("Enter year to delete movies from: ");
    scanf("%d", &year);
    
    int i = 0;
    while (i < num_movies) {
        if (movies[i].year == year) {
            // Shift remaining movies to fill the gap
            for (int j = i; j < num_movies - 1; j++) {
                movies[j] = movies[j + 1];
            }
            num_movies--;
        } else {
            i++;
        }
    }
    
    return num_movies;
}

void reportCurrentMovies(Movie movies[], int num_movies) {
    int current_year;
    printf("Enter current year: ");
    scanf("%d", &current_year);
    
    FILE *file = fopen("reportCM.bin", "wb");
    if (file == NULL) {
        printf("Error creating report file.\n");
    } else {
        int movies_written = 0;
        
        for (int i = 0; i < num_movies; i++) {
            if (movies[i].year == current_year) {
                fwrite(&movies[i], sizeof(Movie), 1, file);
                movies_written++;
            }
        }
        
        fclose(file);
        
        if (movies_written > 0) {
            printf("Report created successfully in reportCM.bin with %d movies from %d\n", 
                   movies_written, current_year);
        } else {
            printf("No movies found from %d\n", current_year);
            remove("reportCM.bin");
        }
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

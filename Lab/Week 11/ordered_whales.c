#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SPECIES_NAME_LENGTH 4096

// a struct to represent the date
// a whale pod sighting was made

struct date {
    int year;
    int month;
    int day;
};

// a struct to represent a sighting
// of a pod (group) of whales

struct pod {
    struct pod *next;
    struct date *when;
    int how_many;
    char *species;
};


struct pod *read_sightings_file(char filename[]);

struct pod *read_sighting(FILE *f);

struct date *read_date(FILE *f);

void write_sightings(FILE *f, struct pod *first_pod);

void write_sighting(FILE *f, struct pod *p);

void write_date(FILE *f, struct date *d);

struct pod *order_whales(struct pod *first_pod);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        return 1;
    }

    struct pod *first_pod = read_sightings_file(argv[1]);

    struct pod *new_first_pod = order_whales(first_pod);
    write_sightings(stdout, new_first_pod);

    return 0;
}


int dateIsBefore(struct date *a, struct date *b);


int dateIsBefore(struct date *a, struct date *b) {
    // https://stackoverflow.com/a/35626495

    if (a->year < b->year) return 1;
    if (a->year == b->year) {
        if (a->month < b->month) return 1;
        if (a->month == b->month && a->day < b->day) return 1;
    }
    return 0;
}

int dateIsEqual(struct date *a, struct date *b) {
    return a->day == b->day && a->month == b->month && a->year == b->year;
}

// return whale list rearranged into increasing (non-decreasing) order

struct pod *order_whales(struct pod *first_pod) {

    // Loop until we reach the end of the list
    int recheck = 1;

    while (recheck) {
        recheck = 0;

        struct pod *current = first_pod;
        struct pod *previous = NULL;

        while (current->next != NULL) {

            int flag_dateBefore = dateIsBefore(current->when, current->next->when);
            int flag_dateSame = dateIsEqual(current->when, current->next->when);
            int flag_specialAlphabetical = strcmp(current->species, current->next->species) < 0;
            int flag_speciesEqual = strcmp(current->species, current->next->species) == 0;
            int flag_numericallyLess = current->how_many <= current->next->how_many;


            int flag = 0;

            // Ordering should be first be chronologically on date, then alphabetically on species, and finally numerically on number of whales seen.
            if (flag_dateBefore) {
                flag = 1;
            } else if (flag_dateSame) {
                if (flag_specialAlphabetical) {
                    flag = 1;
                } else if (flag_speciesEqual) {
                    if (flag_numericallyLess) {
                        flag = 1;
                    }
                }
            }

            if (flag) {
                previous = current;
                current = current->next;
            } else {
                recheck = 1;
                struct pod *a = current;
                struct pod *b = current->next;
                struct pod *c = current->next->next;

                if (previous == NULL) {
                    first_pod = b;
                } else {
                    previous->next = b;
                }

                b->next = a;
                a->next = c;

                previous = b;
            }
        }
    }
    return first_pod;
}


//
// DO NOT CHANGE THE FUNCTIONS BELOW HERE
//

// return linked list of sightings read from filename
// exit called if there is an error

struct pod *read_sightings_file(char filename[]) {
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        fprintf(stderr, "error: file '%s' can not open\n", filename);
        exit(1);
    }

    struct pod *first_sighting = NULL;
    struct pod *last_sighting = NULL;

    struct pod *sighting = read_sighting(f);
    while (sighting != NULL) {
        if (first_sighting == NULL) {
            first_sighting = sighting;
            first_sighting->next = NULL;
        } else {
            last_sighting->next = sighting;
        }
        last_sighting = sighting;
        sighting = read_sighting(f);
    }

    return first_sighting;
}


// read a whale sighting (date, number of whales, whale species)
// return a pointer to a malloced struct containing thes edetails
// return NULL if a sighting can not be read

struct pod *read_sighting(FILE *f) {
    struct pod *p = malloc(sizeof(struct pod));
    if (p == NULL) {
        fprintf(stderr, "out of memory\n");
        exit(1);
    }

    p->next = NULL;

    p->when = read_date(f);
    if (p->when == NULL) {
        free(p);
        return NULL;
    }

    int n_scanned = fscanf(f, "%d", &(p->how_many));
    if (n_scanned != 1) {
        free(p);
        return NULL;
    }

    fgetc(f);
    char species_buffer[MAX_SPECIES_NAME_LENGTH];
    if (fgets(species_buffer, MAX_SPECIES_NAME_LENGTH, f) == NULL) {
        free(p);
        return NULL;
    }
    // finish string at '\n' if there is one
    char *newline_ptr = strchr(species_buffer, '\n');
    if (newline_ptr != NULL) {
        *newline_ptr = '\0';
    }

    // also finish string at '\r' if there is one - files from Windows  will
    newline_ptr = strchr(species_buffer, '\r');
    if (newline_ptr != NULL) {
        *newline_ptr = '\0';
    }

    // malloc a chararray long enough to hold species name
    // and copy species to it
    p->species = malloc(strlen(species_buffer) + 1);
    if (p->species == NULL) {
        fprintf(stderr, "out of memory\n");
        exit(1);
    }
    strcpy(p->species, species_buffer);

    return p;
}


// read a date in day/month/year format from stream f
// return a pointer to a malloced date struct containing them
//  return NULL if a date can not be read

struct date *read_date(FILE *f) {
    struct date *d = malloc(sizeof(struct date));
    if (d == NULL) {
        fprintf(stderr, "out of memory\n");
        exit(1);
    }
    int n_scanned = fscanf(f, "%d/%d/%d", &(d->day), &(d->month), &(d->year));
    if (n_scanned != 3) {
        free(d);
        return NULL;
    }
    return d;
}


// print linked list of sightings to stream f

void write_sightings(FILE *f, struct pod *first_pod) {
    struct pod *p = first_pod;
    while (p != NULL) {
        write_sighting(f, p);
        p = p->next;
    }
}


// print pod details to stream f

void write_sighting(FILE *f, struct pod *p) {
    write_date(f, p->when);
    fprintf(f, " %2d %s\n", p->how_many, p->species);
}


// print date to  stream f

void write_date(FILE *f, struct date *d) {
    fprintf(f, "%02d/%02d/%02d", d->day, d->month, d->year);
}

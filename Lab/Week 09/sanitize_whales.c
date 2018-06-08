#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#define MAX_SPECIES_NAME_LENGTH  128
#define MAX_SIGHTINGS           10000
#define MAX_WHALE_SPECIES         256

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
    struct date when;
    int how_many;
    char species[MAX_SPECIES_NAME_LENGTH];
};


int read_sightings_file(char filename[], int len, struct pod sightings[len]);

int read_sighting(FILE *f, struct pod *p);

int read_date(FILE *f, struct date *d);

void write_sightings_file(char filename[], int n_sightings, struct pod sightings[n_sightings]);

void write_sighting(FILE *f, struct pod *p);

void write_date(FILE *f, struct date *d);

void sanitize_whales(char species_names_file[], int n_sightings, struct pod sightings[n_sightings]);

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <species_names_file> <old_file> <new_file>\n", argv[0]);
        return 1;
    }

    char *species_names_file = argv[1];
    char *old_file = argv[2];
    char *new_file = argv[3];

    struct pod whale_sightings[MAX_SIGHTINGS];
    int n_sightings = read_sightings_file(old_file, MAX_SIGHTINGS, whale_sightings);

    if (n_sightings < 1) {
        return 1;
    }

    sanitize_whales(species_names_file, n_sightings, whale_sightings);

    write_sightings_file(new_file, n_sightings, whale_sightings);

    return 0;
}


//
// correct whales names removing extra characters and correcting case
//

void sanitize_whales(char species_names_file[], int n_sightings, struct pod sightings[n_sightings]) {
    /* Approach
     * ========
     *
     * Since we are finding the most similar specie to the input,
     * we can actually ignore needing to fully sanitise the specie name
     *
     * Instead we can just find the letter similarity.
     * This is done by calculating the sum of case-insensitive letters and finding the specie whose sum is the closest
     */

    int i, j;

    /* READ THE CORRECT NAMES AND CALCULATE THE LETTER SUM */
    char species[MAX_WHALE_SPECIES][MAX_SPECIES_NAME_LENGTH] = {};
    int speciesCharacterSum[MAX_WHALE_SPECIES] = {0};
    int speciesCount = 0;

    FILE *f = fopen(species_names_file, "r");
    i = 0;
    while (fgets(species[i], MAX_SPECIES_NAME_LENGTH, f) != NULL) {

        // Strip off the '\n' character at the end of the string if present
        int len = strlen(species[i]);
        if (len > 0 && species[i][len - 1] == '\n') {
            species[i][len - 1] = '\0';
        }

        // Calculate the sum
        for (j = 0; j < len; j++) {
            if (isalpha(species[i][j])) {
                speciesCharacterSum[i] += toupper(species[i][j]);
            }
        }
        i++;
    }
    speciesCount = i;

    /* ITERATE THROUGH THE SIGHTINGS AND MATCH THE SPECIE */
    for (i = 0; i < n_sightings; i++) {

        // Find the sum of the characters
        int characterSum = 0;
        for (j = 0; j < strlen(sightings[i].species); j++) {
            if (isalpha(sightings[i].species[j])) {
                characterSum += toupper(sightings[i].species[j]);
            }
        }

        // closest index and its absolute sum difference
        int closestIndex  = 0;
        int closestABS = -1;

        // Compare the sum with each specie's sum
        for (j = 0; j < speciesCount; j++) {
            int difference = speciesCharacterSum[j] - characterSum;
            int abs = difference > 0 ? difference : -difference; // Get the magnitude / absolute value // -999 => 999

            // Find if a specie sum is closer (smaller absolute difference)
            if (abs <= closestABS || closestABS == -1) {
                closestIndex = j;
                closestABS = abs;
            }
        }

        // Update the string in the structs
        for (j = 0; j < strlen(species[closestIndex]); j++) {
            sightings[i].species[j] = species[closestIndex][j];
        }
        sightings[i].species[j] = '\0';

        // printf("%s\n", species[closestIndex]);
    }


    // for (i = 0; i < n_sightings; i++) {
    //
    //    // Sanitize strings
    //    for (i = 0; i < n_sightings; i++) {
    //        int k = 0;
    //        char newName[MAX_SPECIES_NAME_LENGTH];
    //        for (j = 0; j < strlen(sightings[i].species); j++) {
    //            if (('a' <= sightings[i].species[j] && sightings[i].species[j] <= 'z')
    //                || ('A' <= sightings[i].species[j] && sightings[i].species[j] <= 'Z')
    //                || (sightings[i].species[j] == ' ' && k != 0)
    //                || sightings[i].species[j] == '-') {
    //                if (!((sightings[i].species[j] == ' ' && k > 0 && newName[k - 1] == ' ')
    //                      || (sightings[i].species[j] == '-' && k > 0 && newName[k - 1] == '-'))) {
    //                    newName[k++] = sightings[i].species[j];
    //                }
    //            }
    //        }
    //
    //        for (j=0;j<k;j++) {
    //            sightings[i].species[j] = newName[j];
    //        }
    //        sightings[i].species[j] = '\0';
    //
    //    }
    //
    //    for (i=0;i<n_sightings;i++) {
    //        printf("%s\n", sightings[i].species);
    //    }


    // REPLACE THIS COMMENT WITH YOUR CODE
    // THIS FUNCTION SHOULD NOT CALL SCANF OR PRINTF
    // IT SHOULD CHANGE THE STRUCTS IN THE ARRAY SIGHTINGS
}


//
// DO NOT CHANGE THE FUNCTION BELOW HERE
//

// return number of sightings read from filename
// -1 is returned if there is an error

int read_sightings_file(char filename[], int len, struct pod sightings[len]) {
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        fprintf(stderr, "error: file '%s' can not open\n", filename);
        return -1;
    }

    int n_sightings = 0;
    while (read_sighting(f, &sightings[n_sightings]) == 1 && n_sightings < len) {
        n_sightings = n_sightings + 1;
    }
    fclose(f);

    return n_sightings;
}


// return 1 if a sighting can be read, 0 otherwise

int read_sighting(FILE *f, struct pod *s) {
    if (read_date(f, &(s->when)) != 1) {
        return 0;
    }
    if (fscanf(f, "%d", &(s->how_many)) != 1) {
        return 0;
    }
    fgetc(f);
    if (fgets(s->species, MAX_SPECIES_NAME_LENGTH, f) == NULL) {
        return 0;
    }
    char *newline_ptr = strchr(s->species, '\n');
    if (newline_ptr != NULL) {
        *newline_ptr = '\0';
    }
    return 1;
}


// print array of sightings to stdout

void write_sightings_file(char filename[], int n_sightings, struct pod sightings[n_sightings]) {
    FILE *f = fopen(filename, "w");
    if (f == NULL) {
        fprintf(stderr, "error: file '%s' can not open\n", filename);
        return;
    }
    int i = 0;
    while (i < n_sightings) {
        write_sighting(f, &sightings[i]);
        i = i + 1;
    }
    fclose(f);
}


// print pod to stdout

void write_sighting(FILE *f, struct pod *s) {
    write_date(f, &(s->when));
    fprintf(f, " %2d %s\n", s->how_many, s->species);
}


// return 1 if a date can be read, 0 otherwise

int read_date(FILE *f, struct date *d) {
    int n_scanned = fscanf(f, "%d/%d/%d", &(d->year), &(d->month), &(d->day));
    return n_scanned == 3;
}


// print date to stdout

void write_date(FILE *f, struct date *d) {
    fprintf(f, "%02d/%02d/%02d", d->year, d->month, d->day);
}
#ifndef ALBUMS_H
#define ALBUMS_H

typedef struct album *ALBUM;

ALBUM create_album(void);

char* get_album_id(ALBUM album);
GArray* get_album_artists_ids(ALBUM album); 
int get_album_year(ALBUM album);

void set_album_id(ALBUM album, char *id);
void set_album_artists_ids(ALBUM album, char *artists_ids_str); 
void set_album_year(ALBUM album, int year);

void free_album(ALBUM album);

#endif

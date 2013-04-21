typedef struct {
	const short *CharacterMap;
	const int *GlyphAdvances;
	int Count;
	VGPath Glyphs[1150];
} Fontinfo;

Fontinfo SansTypeface, SerifTypeface, MonoTypeface, TimesTypeface, ComicTypeface;

 #!/bin/bash
VIDEOFILE=$1;
OUTPUT=$2;
WIDTH=$3;
HEIGHT=$4;

# Generate Pallete for higher quality GIF
ffmpeg -y -ss 1 -t 3 -i $VIDEOFILE \
-vf fps=8,scale=320:-1:flags=lanczos,palettegen /tmp/palette.png

# Generate GIF
ffmpeg -ss 1 -t 3 -i $VIDEOFILE -i /tmp/palette.png -s $WIDTH"x"$HEIGHT -filter_complex \
"fps=8,scale=320:-1:flags=lanczos[x];[x][1:v]paletteuse" $OUTPUT

#  Remove temp pallete file
rm /tmp/palette.png
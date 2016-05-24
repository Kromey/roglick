#!/bin/bash

DIR=$(mktemp -d)
PAGES=""

for img in screenshot*.png; do
	CAPTIONFILE=$(echo $img | sed 's/png$/txt/')
	if [ -e "$CAPTIONFILE" ]; then
		CAPTION=$(cat $CAPTIONFILE)
	fi

	convert $img -resize 50% -fill white -undercolor '#000000A0' -gravity South -annotate +0+5 " $CAPTION " $DIR/$img
	PAGES="$PAGES $DIR/$img"
done

PAGES="$PAGES $DIR/$img"

convert -delay 175 -dispose None $PAGES -loop 0 animation.gif

rm -rf $DIR


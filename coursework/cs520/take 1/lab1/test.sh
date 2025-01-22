#!/bin/bash
# testing lab 1

$1

if [ $1 == 1 ]; then

    # executes program
    echo "executing a.out..."
    ./a.out t1-utf8-letter-x OUTPUT_UTF8_LETTER_X
    echo "program complete."

    # displays expected output
    echo "expected output:"
    od -tx4 OUTPUT_UTF8_LETTER_X_TEST

    # displays program output
    echo "program output:"
    od -tx4 OUTPUT_UTF8_LETTER_X
fi

if [ $1 == 2 ]; then

    # executes program
    echo "executing a.out..."
    ./a.out t1-utf8-1a OUTPUT_UTF8_1A
    echo "program complete."

    # displays expected output
    echo "expected output:"
    od -tx4 OUTPUT_UTF8_1A_TEST

    # displays program output
    echo "program output:"
    od -tx4 OUTPUT_UTF8_1A
fi

if [ $1 == 3 ]; then

    # executes program
    echo "executing a.out..."
    ./a.out t1-utf8-1b OUTPUT_UTF8_1B
    echo "program complete."

    # displays expected output
    echo "expected output:"
    od -tx4 OUTPUT_UTF8_1B_TEST

    # displays program output
    echo "program output:"
    od -tx4 OUTPUT_UTF8_1B
fi
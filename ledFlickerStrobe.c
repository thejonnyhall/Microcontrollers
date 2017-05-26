{\rtf1\ansi\ansicpg1252\cocoartf1404\cocoasubrtf470
{\fonttbl\f0\fnil\fcharset0 Monaco;}
{\colortbl;\red255\green255\blue255;\red109\green109\blue109;\red255\green255\blue255;\red59\green59\blue59;
\red0\green0\blue0;\red10\green82\blue135;\red15\green114\blue1;}
\paperw11900\paperh16840\margl1440\margr1440\vieww10800\viewh8400\viewkind0
\deftab720
\pard\pardeftab720\sl352\partightenfactor0

\f0\fs32 \cf2 \cb3 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \strokec2 #ifndef F_CPU\cf4 \strokec4 \
\cf2 \strokec2 #define F_CPU 16000000UL // or whatever may be your frequency\cf4 \strokec4 \
\cf2 \strokec2 #endif\cf4 \strokec4 \
\'a0\
\cf2 \strokec2 #include <avr/io.h>\cf4 \strokec4 \
\cf2 \strokec2 #include <util/delay.h>\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0 // for _delay_ms()\cf4 \strokec4 \
\'a0\
\cf2 \strokec2 int\cf4 \strokec4  \cf5 \strokec5 main(\cf6 \strokec6 void\cf5 \strokec5 )\cf4 \strokec4 \
\pard\pardeftab720\sl352\partightenfactor0
\cf5 \strokec5 \{\cf4 \strokec4 \
\'a0\'a0\'a0\'a0\cf5 \strokec5 DDRC = 0x01;\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0 \cf7 \strokec7 // initialize port C\cf4 \strokec4 \
\'a0\'a0\'a0\'a0\cf6 \strokec6 while\cf5 \strokec5 (1)\cf4 \strokec4 \
\'a0\'a0\'a0\'a0\cf5 \strokec5 \{\cf4 \strokec4 \
\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\cf7 \strokec7 // LED on\cf4 \strokec4 \
\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\cf5 \strokec5 PORTC = 0b00000001;\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0 \cf7 \strokec7 // PC0 = High = Vcc\cf4 \strokec4 \
\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\cf5 \strokec5 _delay_ms(500);\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0 \cf7 \strokec7 // wait 500 milliseconds\cf4 \strokec4 \
\'a0\
\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\cf7 \strokec7 //LED off\cf4 \strokec4 \
\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\cf5 \strokec5 PORTC = 0b00000000;\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0 \cf7 \strokec7 // PC0 = Low = 0v\cf4 \strokec4 \
\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\cf5 \strokec5 _delay_ms(500);\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0\'a0 \cf7 \strokec7 // wait 500 milliseconds\cf4 \strokec4 \
\'a0\'a0\'a0\'a0\cf5 \strokec5 \}\cf4 \strokec4 \
\cf5 \strokec5 \}}
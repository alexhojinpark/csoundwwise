<CsoundSynthesizer>
<CsOptions>
; -odac
-n
</CsOptions>
<CsInstruments>
sr = 44100
ksmps = 64
nchnls = 1
0dbfs = 1

instr 1
  asig oscili p4,p5
  // aenv, how sound changes in time
  // aenv linen xamp, ireise, idur, idec
  aenv linen asig, 0.1, p3, 0.1
  out aenv
endin

instr 2
  a1 vco2 p4, p5
  a2 vco2 p4, p5*1.002
  a3 vco2 p4, p5*0.998
  a4 vco2 p4, p5*1.004
  a5 vco2 p4, p5*0.996
  a6 vco2 p4, p5*1.006
  a7 vco2 p4, p5*0.994
  amix = (a1+a2+a3+a4+a5+a6+a7)*0.142
  asig linen amix, 0.01, p3, 0.1
  out asig
endin

// Schedule insnum, iwhen, idur, [, ip4] [, ip5], which means...
// schedule(1, start, duration, amplitude, frequency)
// used https://mixbutton.com/mixing-articles/music-note-to-frequency-chart/
// as a reference for note to frequency.

// Cannon Chord Progression in C
// (I - V - vi - iii - IV - I - IV - V)

// Left Hand
// I (Cmaj: C, E, G)
schedule(1, 0, 2, 0dbfs/10, 261.63/2)
schedule(1, 0, 2, 0dbfs/10, 329.63/2)
schedule(1, 0, 2, 0dbfs/12, 392.00/2)

// V (Gmaj: G, B, D)
schedule(1, 2, 2, 0dbfs/10, 392.00/2)
schedule(1, 2, 2, 0dbfs/10, 493.88/2)
schedule(1, 2, 2, 0dbfs/12, 587.33/2)

// vi (Amin: A, C, E)
schedule(1, 4, 2, 0dbfs/10, 440.00/2)
schedule(1, 4, 2, 0dbfs/10, 261.63/2)
schedule(1, 4, 2, 0dbfs/12, 329.63/2)

// iii (Emin: E, G, B)
schedule(1, 6, 2, 0dbfs/10, 329.63/2)
schedule(1, 6, 2, 0dbfs/10, 392.00/2)
schedule(1, 6, 2, 0dbfs/12, 493.88/2)

// IV (Fmaj: F, A, C)
schedule(1, 8, 2, 0dbfs/10, 349.23/2)
schedule(1, 8, 2, 0dbfs/12, 440.00/2)
schedule(1, 8, 2, 0dbfs/10, 261.63/2)

// I (Cmaj: C, E, G)
schedule(1, 10, 2, 0dbfs/10, 261.63/2)
schedule(1, 10, 2, 0dbfs/10, 329.63/2)
schedule(1, 10, 2, 0dbfs/12, 392.00/2)

// IV (Fmaj: F, A, C)
schedule(1, 12, 2, 0dbfs/10, 349.23/2)
schedule(1, 12, 2, 0dbfs/12, 440.00/2)
schedule(1, 12, 2, 0dbfs/10, 261.63/2)

// V (Gmaj: G, B, D)
schedule(1, 14, 0.5, 0dbfs/10, 392.00/2)
schedule(1, 14, 0.5, 0dbfs/12, 493.88/2)
schedule(1, 14, 0.5, 0dbfs/12, 587.33/2)

// 2nd Verse
// I (Cmaj: C, E, G)
schedule(2, 16, 2, 0dbfs/10, 261.63/2)
schedule(2, 16, 2, 0dbfs/10, 329.63/2)
schedule(2, 16, 2, 0dbfs/12, 392.00/2)
schedule(1, 16, 2, 0dbfs/15, 261.63*2)
schedule(1, 16, 2, 0dbfs/15, 329.63*2)
schedule(1, 16, 2, 0dbfs/15, 392.00*2)


// V (Gmaj: G, B, D)
schedule(2, 18, 2, 0dbfs/10, 392.00/2)
schedule(2, 18, 2, 0dbfs/10, 493.88/2)
schedule(2, 18, 2, 0dbfs/12, 587.33/2)
schedule(1, 18, 2, 0dbfs/15, 392.00*2)
schedule(1, 18, 2, 0dbfs/15, 493.88*2)
schedule(1, 18, 2, 0dbfs/15, 587.33*2)


// vi (Amin: A, C, E)
schedule(2, 20, 2, 0dbfs/10, 440.00/2)
schedule(2, 20, 2, 0dbfs/10, 261.63/2)
schedule(2, 20, 2, 0dbfs/12, 329.63/2)
schedule(1, 20, 2, 0dbfs/15, 440.00*2)
schedule(1, 20, 2, 0dbfs/15, 261.63*2)
schedule(1, 20, 2, 0dbfs/15, 329.63*2)


// iii (Emin: E, G, B)
schedule(2, 22, 2, 0dbfs/10, 329.63/2)
schedule(2, 22, 2, 0dbfs/10, 392.00/2)
schedule(2, 22, 2, 0dbfs/12, 493.88/2)
schedule(1, 22, 2, 0dbfs/15, 329.63*2)
schedule(1, 22, 2, 0dbfs/15, 392.00*2)
schedule(1, 22, 2, 0dbfs/15, 493.88*2)


// IV (Fmaj: F, A, C)
schedule(2, 24, 2, 0dbfs/10, 349.23/2)
schedule(2, 24, 2, 0dbfs/12, 440.00/2)
schedule(2, 24, 2, 0dbfs/10, 261.63/2)
schedule(1, 24, 2, 0dbfs/15, 349.23*2)
schedule(1, 24, 2, 0dbfs/15, 440.00*2)
schedule(1, 24, 2, 0dbfs/15, 261.63*2)

// I (Cmaj: C, E, G)
schedule(2, 26, 2, 0dbfs/10, 261.63/2)
schedule(2, 26, 2, 0dbfs/10, 329.63/2)
schedule(2, 26, 2, 0dbfs/12, 392.00/2)
schedule(1, 26, 2, 0dbfs/15, 261.63*2)
schedule(1, 26, 2, 0dbfs/15, 329.63*2)
schedule(1, 26, 2, 0dbfs/15, 392.00*2)

// IV (Fmaj: F, A, C)
schedule(2, 28, 2, 0dbfs/10, 349.23/2)
schedule(2, 28, 2, 0dbfs/12, 440.00/2)
schedule(2, 28, 2, 0dbfs/10, 261.63/2)
schedule(1, 28, 2, 0dbfs/15, 349.23*2)
schedule(1, 28, 2, 0dbfs/15, 440.00*2)
schedule(1, 28, 2, 0dbfs/15, 261.63*2)

// V (Gmaj: G, B, D)
schedule(2, 30, 0.25, 0dbfs/10, 392.00/2)
schedule(2, 30, 0.25, 0dbfs/10, 493.88/2)
schedule(2, 30, 0.25, 0dbfs/10, 587.33/2)
schedule(1, 30, 0.25, 0dbfs/15, 392.00*2)
schedule(1, 30, 0.25, 0dbfs/15, 493.88*2)
schedule(1, 30, 0.25, 0dbfs/15, 587.33*2)

schedule(2, 30.25, 0.25, 0dbfs/10, 392.00/2)
schedule(2, 30.25, 0.25, 0dbfs/10, 493.88/2)
schedule(2, 30.25, 0.25, 0dbfs/10, 587.33/2)
schedule(1, 30.25, 0.25, 0dbfs/15, 392.00*2)
schedule(1, 30.25, 0.25, 0dbfs/15, 493.88*2)
schedule(1, 30.25, 0.25, 0dbfs/15, 587.33*2)


// Right Hand
// I (Cmaj: C, E, G)
schedule(2, 0, 0.5, 0dbfs/15, 261.63)
schedule(2, 0.25, 0.5, 0dbfs/15, 329.63)
schedule(2, 0.5, 0.5, 0dbfs/15, 392.00)

// V (Gmaj: G, B, D)
schedule(2, 2, 0.5, 0dbfs/15, 392.00)
schedule(2, 2.25, 0.5, 0dbfs/15, 493.88)
schedule(2, 2.5, 0.5, 0dbfs/15, 587.33)

// vi (Amin: A, C, E)
schedule(2, 4, 0.5, 0dbfs/10, 440.00)
schedule(2, 4.25, 0.5, 0dbfs/10, 261.63)
schedule(2, 4.5, 0.5, 0dbfs/12, 329.63)

// iii (Emin: E, G, B)
schedule(2, 6, 0.5, 0dbfs/10, 329.63)
schedule(2, 6.25, 0.5, 0dbfs/10, 392.00)
schedule(2, 6.5, 0.5, 0dbfs/12, 493.88)

// IV (Fmaj: F, A, C)
schedule(2, 8, 0.5, 0dbfs/10, 349.23)
schedule(2, 8.25, 0.5, 0dbfs/12, 440.00)
schedule(2, 8.5, 0.5, 0dbfs/10, 261.63)

// I (Cmaj: C, E, G)
schedule(2, 10, 0.5, 0dbfs/10, 261.63)
schedule(2, 10.25, 0.5, 0dbfs/10, 329.63)
schedule(2, 10.5, 0.5, 0dbfs/12, 392.00)

// IV (Fmaj: F, A, C)
schedule(2, 12, 0.5, 0dbfs/10, 349.23)
schedule(2, 12.25, 0.5, 0dbfs/12, 440.00)
schedule(2, 12.5, 0.5, 0dbfs/10, 261.63)

// V (Gmaj: G, B, D)
schedule(2, 14, 0.5, 0dbfs/12, 392.00)
schedule(2, 14.25, 0.5, 0dbfs/12, 493.88)
schedule(2, 14.5, 0.5, 0dbfs/12, 587.33)
</CsInstruments>

<CsScore>
; f 0 35 // play for 35 sec
</CsScore>

</CsoundSynthesizer>

<CsoundSynthesizer>
<CsOptions>
-n
</CsOptions>
<CsInstruments>

sr = 44100
ksmps = 64
nchnls = 1
0dbfs = 1

instr Hello
  aSine = poscil:a(0.2,400)
  out aSine
endin

instr 1
	ifna = p9 		; amplitude env table
	ifnb = p10		; timbre env table
	ae oscili  p4, 1/p3, ifna
	ai oscili (p8-p7)*p6, 1/p3, ifnb
	am oscili  p7*p6 + ai, p6
	ac oscili  ae, am + p5 
	out ac  
endin

// Soft Brass tone
ia ftgen 0, 0, 1024, 7, 0, 100, 1, 100, 0.7, 724, 0.7, 100, 0
schedule(1, 0, 0.6, 0.5, 196, 196, 0, 2, ia, ia)
schedule(1, 0.6, 0.45, 0.5, 220, 220, 0, 2, ia, ia)
schedule(1, 1.1, 0.45, 0.5, 233.08, 233.08, 0, 2, ia, ia)
schedule(1, 1.55, 10.8, 0.5, 311.13, 311.13, 0, 2, ia, ia)

</CsInstruments>
<CsScore>
; i "Hello" 0 3600
; i 1 0 3600 0.5 196 196 0 2 ia ia
</CsScore>
</CsoundSynthesizer>
















<bsbPanel>
 <label>Widgets</label>
 <objectName/>
 <x>100</x>
 <y>100</y>
 <width>320</width>
 <height>240</height>
 <visible>true</visible>
 <uuid/>
 <bgcolor mode="background">
  <r>240</r>
  <g>240</g>
  <b>240</b>
 </bgcolor>
</bsbPanel>
<bsbPresets>
</bsbPresets>

estaEnsolarado.
tenhoTempoLivre.
!pegarUmBronzeado.
!aproveitarOdia.
+!pegarUmBronzeado: estaEnsolarado & tenhoTempoLivre <- irParaAPraia ; passarProtetorSolar ; deitarNoSol. 
+!aproveitarOdia: not estaEnsolarado <- sair ; encontrarUmLugarCoberto ; fazerAlgumaAtividadeInterna. 
+!aproveitarOdia: estaEnsolarado & tenhoTempoLivre <- sairPorUmTempoLimitado ; aproveitarOQuePuder. 

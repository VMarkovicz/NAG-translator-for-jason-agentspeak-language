estaChovendo.
naotenhoGuardaChuva.
!comprarGuardaChuva.
!naoPegarChuva.
+!comprarGuardaChuva: estaChovendo & naotenhoGuardaChuva <- sair ; procurarLoja ; comprarGuardaChuva. 
+!naoPegarChuva: not estaChovendo <- sair ; jogarBola. 
+!naoPegarChuva: estaChovendo & naotenhoGuardaChuva <- ficarEmCasa ; estudar. 

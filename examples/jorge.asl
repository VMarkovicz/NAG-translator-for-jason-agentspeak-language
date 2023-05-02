estaAtrasado.
estaComFome.
!chegarNoTrabalhoNaHora.
!comerAlgumaCoisa.
!serProdutivo.
+!chegarNoTrabalhoNaHora: not estaAtrasado <- sair ; pegarOnibus. 
+!chegarNoTrabalhoNaHora: estaAtrasado <- sair ; pegarTaxi. 
+!comerAlgumaCoisa: estaComFome <- sair ; encontrarRestaurante ; pedirComida. 
+!serProdutivo: not estaComFome <- trabalhar ; focarNasTarefas. 

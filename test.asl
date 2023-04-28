agent Bob {
    beliefs: {
        estaChovendo;
        naoTenhoGuardaChuva;
    }
    goals: {
        comprarGuardaChuva;
        naoPegarChuva;
    }
    plans: {
        plano1: (
            comprarGuardaChuva;
            estaChovendo & naoTenhoGuardaChuva;
            (
                sair;
                procurarLoja;
                comprarGuardaChuva;
            )
        );
        plano2: (
            naoPegarChuva;
            nao estaChovendo;
            (
                sair;
                jogarBola;
            )
        );
        plano3: (
            naoPegarChuva;
            estaChovendo & naoTenhoGuardaChuva;
            (
                ficarEmCasa;
                estudar;
            )
        );
    }
}

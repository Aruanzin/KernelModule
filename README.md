# KernelModule
 implementação de um módulo de kernel para Linux que atue como um agente backdoor

 # Como Executar:
 Comandos:
 pasta do modulo: sudo su
pasta do modulo: make
pasta do modulo: insmod dvt-driver.ko
pasta do modulo: dmesg --follow(caso queria ver as msgs do kernel)
pasta do modulo:rmmod dvt_driver (para remover o modulo do kernel)

dentro da pasta de servidores:
python3 pythonServer.py (starta servidor)
python3 pythonClient.py(starta client)

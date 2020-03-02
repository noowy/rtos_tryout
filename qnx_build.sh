vm_ip=192.168.1.80
function build_deploy {
    if [ "$1" == "lab_ipc" ]
    then
        ./x86_64-pc-nto-qnx7.0.0-gcc.exe -o ./walkie.out /c/My_Software/C/rtos_qnx_labs/lab_ipc/walkie/src/*
        ./x86_64-pc-nto-qnx7.0.0-gcc.exe -o ./talkie.out /c/My_Software/C/rtos_qnx_labs/lab_ipc/talkie/src/*
        ./x86_64-pc-nto-qnx7.0.0-gcc.exe -o ./http_tx.out /c/My_Software/C/rtos_qnx_labs/lab_ipc/http_tx/src/*
        scp -r ./walkie.out ./talkie.out ./http_tx.out qnxuser@$vm_ip:/home/qnxuser/
        ssh qnxuser@$vm_ip "chmod +x ./walkie.out ./talkie.out ./http_tx.out"
    else
        ./x86_64-pc-nto-qnx7.0.0-gcc.exe -o $1.out /c/My_Software/C/rtos_qnx_labs/$1/src/*
        scp $1.out qnxuser@$vm_ip:/home/qnxuser/
        ssh qnxuser@$vm_ip "chmod +x ./$1.out"
    fi
}

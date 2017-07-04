#Declaration du project
project(libmodbus)

#Declaration de l'executable
add_executable(

		my_executable
		
		src/modbus.c
		
		src/modbus.h
		
		src/modbus-data.c
		
		src/modbus-private.h
		
		src/modbus-rtu.c
		
		src/modbus-rtu.h
		
		src/modbus-rtu-private.h
		
		src/modbus-tcp.c
		
		src/modbus-tcp.h
		
		src/modbus-tcp-private.h
		
		src/modbus-version.h
	
		src/modbus-version.h.in
	
		src/Makefile.am
		
		src/Makefile.in
		
		
		
		
		
)
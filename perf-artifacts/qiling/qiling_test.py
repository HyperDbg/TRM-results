from qiling import Qiling
from qiling.const import QL_VERBOSE
import ctypes

if __name__ == "__main__":


    
    # Load the shared library
    lib = ctypes.CDLL('./librdtscp.so')
    #lib = ctypes.CDLL('./librdtscp.dll')

    # Call the rdtscp function
    lib.rdtscp.restype = ctypes.c_uint64
    total_time = 0
    sample_num = 100
    
    for i in range(0,sample_num) :
        
        # initialize Qiling instance, specifying the executable to emulate and the emulated system root.
        # note that the current working directory is assumed to be Qiling home
        ql = Qiling([r'rootfs/x86_linux/test'], r'rootfs/x86_linux', verbose=QL_VERBOSE.DEBUG)
        # ql = Qiling([r'rootfs/ConsoleApplication1.exe'], r'rootfs/x8664_windows')
        
        timestamp1 = lib.rdtscp()

        # print(f"RDTSCP timestamp: {timestamp1}")
    
        # start emulation
        ql.run() 
    
        timestamp2 = lib.rdtscp()
        
        total_time = total_time + (timestamp2 - timestamp1)
    
    print(f"Totatl RDTSCP timestamp: {total_time}")
    print(f"Average RDTSCP timestamp: {total_time/sample_num}")
    






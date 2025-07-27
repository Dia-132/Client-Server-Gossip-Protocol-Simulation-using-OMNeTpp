
def generate_tictoc_ned(num_tic, num_toc):
    with open("topo.ned", "w") as file:
        file.write("// Generated NED file for the TicToc9 simulation.\n")
        file.write("// This file outlines the network configuration using Tic9 and Toc9 modules.\n\n")
        
        # Include necessary NED channel import
        file.write("import ned.IdealChannel;\n\n")
        
        # Definition for Tic9 module
        file.write("simple Tic9\n")
        file.write("{\n")
        file.write("    parameters:\n")
        file.write("        @display(\"i=block/routing\");\n")
        file.write("    gates:\n")
        file.write("        input in[];\n")
        file.write("        output out[];\n")
        file.write("        input in_c[];\n")
        file.write("        output out_c[];\n")
        file.write("}\n\n")
        
        # Definition for Toc9 module
        file.write("simple Toc9\n")
        file.write("{\n")
        file.write("    parameters:\n")
        file.write("        @display(\"i=block/process\");\n")
        file.write("    gates:\n")
        file.write("        input in[];\n")
        file.write("        output out[];\n")
        file.write("}\n\n")
        
        # Define the overall network structure
        file.write("network Network\n")
        file.write("{\n")
        file.write("    @display(\"bgb=555,405\");\n")
        file.write("    submodules:\n")
        
        # Create Tic9 submodules dynamically
        for i in range(num_tic):
            file.write(f"        tic{i}: Tic9 {{ @display(\"i=,cyan;p={58+i*220},238\"); }}\n")
            
        # Create Toc9 submodules dynamically
        for i in range(num_toc):
            file.write(f"        toc{i}: Toc9 {{ @display(\"i=,gold;p={81+i*73},100\"); }}\n")
            
        file.write("\n")
        file.write("    connections:")
        file.write("\n")
        # Connect each Tic9 and Toc9 module with defined delay
        for i in range(num_tic):
            for j in range(num_toc):
                file.write(f"       tic{i}.out++ --> {{  delay = 200ms; }} --> toc{j}.in++;\n")
                file.write(f"       toc{j}.out++ --> {{  delay = 200ms; }} --> tic{i}.in++;\n")
                
        # Establish additional communication links among Tic9 modules
        for i in range(num_tic):
            for j in range(i+1, num_tic):
                file.write(f"       tic{i}.out_c++ --> {{  delay = 200ms; }} --> tic{(j)%num_tic}.in_c++;\n")
                file.write(f"       tic{j}.out_c++ --> {{  delay = 200ms; }} --> tic{(i)%num_toc}.in_c++;\n")
            
        file.write("}\n")

# Request user input for module counts
num_tic = int(input("Enter the number of Client modules: "))
num_toc = int(input("Enter the number of Server modules: "))

# Create the topo.ned file using the provided module counts
generate_tictoc_ned(num_tic, num_toc)


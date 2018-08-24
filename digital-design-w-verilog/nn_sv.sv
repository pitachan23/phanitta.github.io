module nn_sv(L2_ax,L1_s,L1_th1,L1_th2);

parameter N1; // num of synapses (layer 1)
parameter N2 = 2; // num of synapses (layer 2)

input [N1-1:0] L1_s;
//input [N2*32-1:0] L1_th; // two threshold for neuron 1 and 2 (layer 1)
input [31:0] L1_th1; // threshold for first neuron
input [31:0] L1_th2; // threshold for second neuron
//output reg L2_ax;
output wire L2_ax;

reg [N1*32-1:0] L1_w = {32'b10000000,32'b1000000,32'b100000,32'b10000,32'b1000,32'b100,32'b10,32'b1}; // same weights for both neuron 1 and 2
reg [N2*32-1:0] L2_w = {32'b11111111111111111111111111111111,32'b1}; // weights are +1 and -1 for L1_ax[0] and L1_ax[1]
reg [31:0] L2_th = 32'b1; // th = 1
//reg [N2-1:0] L1_ax; // L1_ax[0] for neuron 1, L1_ax[1] for neuron 2
wire [N2-1:0] L1_ax; // L1_ax[0] for neuron 1, L1_ax[1] for neuron 2

generate
   //genvar i;

   begin: layer1_neuron1
      neuron #(N1) L1_n1 (.axon(L1_ax[0]), .synapses(L1_s), .threshold(L1_th1), .weights(L1_w));
   end

   begin: layer1_neuron2
      neuron #(N1) L1_n2 (.axon(L1_ax[1]), .synapses(L1_s), .threshold(L1_th2), .weights(L1_w));
   end

   begin: layer2_neuron
      neuron #(N2) L2_n (.axon(L2_ax), .synapses(L1_ax), .threshold(L2_th), .weights(L2_w));
   end

endgenerate
/*
initial 
begin
// initialize weights
L1_w <= {32'b10000000,32'b1000000,32'b100000,32'b10000,32'b1000,32'b100,32'b10,32'b1};
L2_w <= {32'b11111111111111111111111111111111,32'b1}; // concatenate w2(-1) and w1(+1)
end
*/
endmodule 




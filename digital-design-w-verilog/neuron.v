module neuron (axon, synapses, weights, threshold);
parameter N;
integer i;
reg [31:0] sum;
reg [31:0] a;
reg [31:0] b;

input [N-1:0] synapses;
input [N*32-1:0] weights; 
input [31:0] threshold;
output reg axon;

always @(synapses)
begin   
   //$write("synapses "); $display("%b",synapses);
   sum = 0; 
   for (i = 0; i < N; i = i+1) begin
      a = weights[i*32+:32];
      b = synapses[i]*a;
      sum = sum + b;
      //$write("a"); $display("%b",a);
      //$write("synapses[]"); $display("%b",synapses[i]);
      //$write("b"); $display("%b",b);
   end

   //$write("sum"); $display("%b",sum);
   //$write("threshold"); $display("%b",threshold);

   if (sum >= threshold)
      axon = 1'b1;
   else
      axon = 1'b0; 
   
   //$write("axon "); $display(axon);
end
endmodule 



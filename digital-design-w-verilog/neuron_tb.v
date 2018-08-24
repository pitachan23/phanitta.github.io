module neuron_tb();

parameter N = 4;
integer i;

reg [N*32-1:0] w = {32'b1000,32'b0100,32'b0010,32'b0001};
reg [31:0] th = 32'b010; // threshold = 0
reg [N-1:0] s;// = 4'b0000;
wire ax;

neuron #(N) nrn (ax, s, w, th); //(.axon(ax1), .synapses(L1_s), .threshold(L1_th1), .weights(L1_w));

initial
begin
   s <= 4'b0000;
   $write("s"); $display("%b",s);
   $write("ax"); $display(ax);
   #30
   s <= s + 1'b1;
   $write("s"); $display("%b",s);
   $write("ax"); $display(ax);
   #30
   s <= s + 1'b1;
   $write("s"); $display("%b",s);
   $write("ax"); $display(ax);
   #30
   s <= s + 1'b1;
   $write("s"); $display("%b",s);
   $write("ax"); $display(ax);
   #30
   s <= s + 1'b1;
   #30
   $write("s"); $display("%b",s);
   $write("ax"); $display(ax);
   s <= s + 1'b1;
   #30
   $write("s"); $display("%b",s);
   $write("ax"); $display(ax);

/*
   for (i = 0; i < 10; i = i+1) begin
      #25
      $write("ax"); $display(ax);
      s = s + 1'b1;
   end
*/
/*
   for (i = 0; i < N; i = i+1) begin
      b = w[i*4+:4];
      a = s[i]*b;
      sum = sum + a;
      $write("b"); $display("%b",b);
      $write("s["); $write(i); $write("]"); $display("%b",s[i]); 
      $write("a"); $display("%b",a);
      $write("sum"); $display("%b",sum);
   end

   if (sum >= th)
      ax = 1'b1;
   else
      ax = 1'b0; 
   $write("ax"); $display(ax);
*/
end
endmodule 



module approx_sv();

parameter N1 = 8;
// 51 boxes, height range [1,25] (approximated by hands)
integer height[0:50] = '{1,3,5,7,9,11,13,15,15,16,17,19,20,21,23,23,24,24,25,25,25,24,24,23,22,22,21,21,20,18,18,18,18,18,18,18,17,17,17,18,18,18,18,18,18,18,18,17,16,16,15}; 
reg [31:0] th1, th2;
//reg [2*32-1:0] th; // th = {th2,th1}
reg [N1-1:0] s; 
wire axon;
integer i,j;

reg [N1*32-1:0] ax;
//integer scale_box[0:255], sum_box[0:255];

//integer try[0:3] = '{26, 40, 32, 23};
//reg [7:0] mem [0:3];// = '{26, 40, 32, 23};
reg [7:0] scale_box [0:255];
reg [7:0] sum_box [0:255];

nn_sv #(N1) nrn (.L2_ax(axon), .L1_s(s), .L1_th1(th1), .L1_th2(th2));
// Boxes
//nn_sv BOX1(axon,synapses,th);

// create an array of axon for each box
// sum up the boxes to get final plot
/*
generate

   begin: build_box
      nn_sv #(N1) nrn (.L2_ax(axon), .L1_s(s), .L1_th1(th1), .L1_th2(th2));
   end

endgenerate
*/
initial
begin
// initialization
   th1 = 32'b0; // 0 -> increment by 5
   th2 = 32'b101; // 5 -> increment by 5
   s = 8'b0;
   //$display("mem: ");
   //mem[0] <= 8'd25;
   //$display(mem[0]);
   for (i = 0; i < 256; i = i+1) begin
      scale_box[i] = 0;
      sum_box[i] = 0;
      //$display(sum_box[0]);
   end
   //for (i = 0; i < 4; i = i+1) begin
   //   mem[i] = 8'd5;
   //end
   //scale_box[1] = 8'd25;
   //$display(scale_box[0]);
   //$display(scale_box[1]);
   //$display(scale_box[2]);
   //$display(sum_box);
/*   
   $display(mem[0]);
   mem[0] = 8'd33;
   $display(mem[0]);
   mem[0] = mem[0]*height[1];
   $display(mem[0]);

   $display("here you go");
   for (i = 0; i < 4; i = i+1) begin
      $display(mem[i]);
   end
*/

// get boxes
   for (i = 0; i < 51; i = i+1) begin
      for (j = 0; j < 256; j = j+1) begin
         ax[j] = axon;
         scale_box[j] = ax[j]*height[i];
         sum_box[j] = sum_box[j]+scale_box[j];
         //$write("j: ");
	 //$write(j);
 	 //$write(", axon: ");
	 //$display(axon);
	 #30
         // update synapses
         s = s + 8'b1; 
      end
      // update thresholds
      th1 = th1 + 32'b101; // increment by 5
      th2 = th2 + 32'b101; // increment by 5
   end

// disp 
   //$display(sum_box);

end
endmodule



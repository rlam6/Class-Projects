import "DPI-C" context encoder= function void encoder(input int data, output int outData,  output int parity );



module dpi_example ();
   parameter size = 15;
   parameter p_size = 4;

   logic   dpi_out [1:size];
   logic   dpi_p_out [1:p_size];


   logic   [1:11] rtl_data_in;
   logic   [1:15] rtl_data_out;
   logic   [1:15] exp_data_out;
   logic   [1:4] parity_out;

   logic   [1:11] C_data_out;
   logic   [1:11] decoder_data_out;

   bit clk;       

   initial begin
      clk =0;
      #80;
      $finish;
   end

   always #1 clk = ~clk;

   always @(posedge clk) begin // Sending Data to C Program
       
      rtl_data_in = $urandom % 2048; //generate random data
      $display("rtl_in: %b", rtl_data_in);      //display the random data 
      encoder(rtl_data_in, C_data_out, parity_out); // feed the data to c programming

      exp_data_out = {parity_out[1:2], C_data_out[1], parity_out[3], C_data_out[2:4],
			parity_out[4], C_data_out[5:11]};
      $display("parity: %b\nc_data_out: %b\n", parity_out, C_data_out); 
   end
   
   // generate the rtl output
   HE L1( .DIN(rtl_data_in), .DOUT(rtl_data_out));
   HD L2( .DIN(exp_data_out), .DOUT(decoder_data_out) );

   //compare expected output and rtl output
   always @(negedge clk) begin
       if (exp_data_out == rtl_data_out) begin
           $display("%t: PASS, Input: %b, Output (EXP/RTL) (%b/%b)", $time, rtl_data_in, exp_data_out, rtl_data_out);
       end else begin
           $display("%t: FAIL, Input: %b, Output (EXP/RTL) (%b/%b)", $time, rtl_data_in, exp_data_out, rtl_data_out);
       end
   end
   always @(decoder_data_out) begin
	if (decoder_data_out == rtl_data_in) begin
           $display("%t: PASS, Input: %b, Output (DECODER) (%b)", $time, rtl_data_in, decoder_data_out);
	end else begin
           $display("%t: FAIL, Input: %b, Output (DECODER) (%b)", $time, rtl_data_in, decoder_data_out);
	end
   end
endmodule

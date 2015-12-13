module processor_tb ();
   parameter aBit = 6;
   parameter nBit = 32;	
   parameter instructionLength = 16;

   bit clk;
   logic   rst;
   logic   request;
   logic   [aBit-1:0] addr;
   wire    [nBit-1:0] dout;
   wire    acknowledge;
   wire    carry, overflow, equal;

   int   testAddr;
   logic   [instructionLength:1][nBit-1:0] instruction_results;

	initial begin
		// Initialize test address index
		testAddr = -1;

		// Assign instruction Results
		instruction_results[1] = 32'b11111111111111111111111111111111; // $s0 = (1111...1111)
		instruction_results[2] = 32'b00000000000000000000000000000001; // $s1 = 1
		instruction_results[3] = 32'b00000000000000000000000000000010; // $s2 = 2
		instruction_results[4] = 32'b00000000000000000000000000000000; // $s3 = 0
		instruction_results[5] = 32'b00000000000000000000000000000011; // $s4 = 3
		instruction_results[6] = 32'b00000000000000000000000000000100; // $s5 = 4
		instruction_results[7] = 32'b00000000000000000000000000000000; // $s6 = $s1 + $s0
		instruction_results[8] = 32'b11111111111111111111111111111100; // $s7 = NOT $s4
	        instruction_results[9] = 32'b11111111111111111111111111111110; // $s8 = $s0 - $s1
	       instruction_results[10] = 32'b11111111111111111111111111111111; // $s8 = $s1 + $s8
	       instruction_results[11] = 32'b11111111111111111111111111111101; // $s8 = $s8 - $s2
	       instruction_results[12] = 32'b00000000000000000000000000000000; // $s10 = $s0 XOR (111..1111)
	       instruction_results[13] = 32'b00000000000000000000000000000010; // $s10 = $s2 AND $s4
	       instruction_results[14] = 32'b00000000000000000000000000000000; // $s10 = $s3 COMP 1111..111
	       instruction_results[15] = 32'b00000000000000000000000000000100; // $s11 = $s5
	       instruction_results[16] = 32'b11111111111111111111111111111110; // $s11 = $s0 SLL 1


		$display ("Writing...");

		// Initialize clock, request, reset signals
		clk =0;
		request = 1; 
		rst =1; 

		// Assign addresses into DMA
		addr = 1; #50 addr = 2; #50 addr = 3; #50 addr = 4; 
		#50 addr = 5; #50 addr = 6; #50 addr = 7; #50 addr = 8; 
		#50 addr = 9; #50 addr = 10; #50 addr = 11; #50 addr = 12; #50 addr = 13; 
		#50 addr = 14; #50 addr = 15; #50 addr = 16;

		#350;
		$display ("Reading...");

		// Start reading
		request = 0;
		rst = 0;

		#400;
		$finish;
	end

	always #10 clk = ~clk;
   

	always @(negedge clk) begin 
		$display("%t: Address into DMA: %b - %d\n", $time, addr, addr); 
	end
	
   
   processor L1(  .clk(clk), 
		.request(request),
		.rst(rst),
		.addr(addr),
		.dout(dout),
		.acknowledge(acknowledge),
		.carry(carry), .equal(equal), .overflow(overflow));


   always @(posedge clk)
   #10 begin
	if (rst == 0) begin
			testAddr++;
			if (testAddr < 1 || testAddr > instructionLength || testAddr == 0) begin
				$display("%t: PASS: NO OUTPUT NECESSARY", $time);
			end
			else if (instruction_results[testAddr] == dout) begin
				$display("%t: PASS, Output (EXP/ACT) (%b/%b)", $time, instruction_results[testAddr], dout);	
			end
			else begin
				$display("%t: FAIL, Output (EXP/ACT) (%b/%b)", $time, instruction_results[testAddr], dout);	
			end	
  
			
	end
end
endmodule


module counter_tb ();

   bit clk;
   logic   rst_s;
   logic   [31:0] din;
   logic   preLoad;
   logic   asc;
   logic   [31:0] dout;
   logic   [31:0] prevData;

	initial begin
		clk =1;
		rst_s =1;
		preLoad =0;
		asc =0;
		prevData =0;
		$display("\nReset values\n");
		#51;
		rst_s = 0;
		asc = 1;
		$display("\nAscend");
		#60;
		preLoad = 1;
		$display("\nPre Load");
		#60;
		preLoad = 0;
		$display("\nAscend");
		#60;
		asc = 0;
		$display("Descend");
		#50;
		$finish;
	end

	always #10 clk = ~clk;
   

	always @(negedge clk) begin // Sending Data to C Program
		prevData = dout;
		din = $urandom % 16;
		$display("Input: %b\n", din); 
	end
	
   
   counter L1(  .clk(clk), 
		.rst_s(rst_s),
		.din(din),
		.preLoad(preLoad),
		.asc(asc),
		.dout(dout));

   always @(posedge clk)
   #10 begin
	if (rst_s == 1)
	begin
		if (dout == 0)
		begin
			$display("%t: PASS, Input: %b, Output (EXP/ACT) (%b/%b)", $time, din, 0, dout);
	end
		else begin
			$display("%t: FAIL, Input: %b, Output (EXP/ACT) (%b/%b)", $time, din, 0, dout);
		end
	end
	else if (preLoad == 1)
	begin
		if (dout == din)
		begin
			$display("%t: PASS, Input: %b, Output (EXP/ACT) (%b/%b)", $time, din, din, dout);
		end
		else begin
			$display("%t: FAIL, Input: %b, Output (EXP/ACT) (%b/%b)", $time, din, din, dout);
		end
	end
	else if (asc == 1)
	begin
		if (dout == prevData + 1)
		begin
			$display("%t: PASS, Previous Data: %b, Output (EXP/ACT) (%b/%b)", $time, prevData, prevData+1, dout);
		end
		else begin
			$display("%t: FAIL, Previous Data: %b, Output (EXP/ACT) (%b/%b)", $time, prevData, prevData+1, dout);
		end
	end
	else if (asc == 0)
	begin
		if (dout == prevData - 1)
		begin
			$display("%t: PASS, Previous Data: %b, Output (EXP/ACT) (%b/%b)", $time, prevData, prevData-1, dout);
		end
		else begin
			$display("%t: FAIL, Previous Data: %b, Output (EXP/ACT) (%b/%b)", $time, prevData, prevData-1, dout);
		end
	end
   

end
endmodule


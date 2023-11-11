using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClassLibrary
{
    public class Integral_Calculation
    {
        delegate void Integral_Calculation_Delegate();
        event Integral_Calculation_Delegate progress;        


        public static Semaphore sem = new Semaphore(2, 2);
        public int percentage { get; set; }

        public Thread thread;
        public double result { get; set; }

        public int Number { get; set; }
        public string elapsed_time { get; set; }
        
        public Integral_Calculation(ThreadPriority priotity = ThreadPriority.Normal, int number = 0)
        {
            progress += display_progress;
            result = 0;
            percentage = 0;
            thread = new Thread(Intergral_Calculation);
            thread.Priority = priotity;
            thread.Start();
            Number = number;
        }

        public void Intergral_Calculation()
        {
            Console.WriteLine($"Thread {Number} is waiting to start.");
            sem.WaitOne();           
            Stopwatch stopWatch = new Stopwatch();
            stopWatch.Start();
            Console.WriteLine($"Thread {Number} started.");

            double delta = 0.0000001; 
            result = 0;
            percentage = 0;
             
            for (double i = 0; i <= 1; i += delta)
            {
                result += Math.Sin(i) * delta;
                percentage = (int)(i / 1.0 * 100);
                double buf = 0;
                for (int j = 0; j < 1000; j++)
                {
                    buf += j;
                }
                
            }
            percentage = 100;

            stopWatch.Stop();
            TimeSpan ts = stopWatch.Elapsed;

            elapsed_time = String.Format("{0:00}:{1:00}:{2:00}",
                ts.Minutes, ts.Seconds,
                ts.Milliseconds / 10);
            string res = $"Thread number {Number} finished. Elapsed Time: {elapsed_time}, Result: {result}";
            Console.WriteLine($"Thread number {Number} finished. Elapsed Time: {elapsed_time}, Result: {result}");
            sem.Release();
            return;
        }

        public void display_progress()
        {
            int number_of_signs = (int)(percentage);
            string progress = "[";
            for (int i = 0; i < 100; i++)
            {
                if (i < number_of_signs)
                {
                    progress += "=";
                }else if (i == number_of_signs){
                    progress += ">";
                }
                else
                {
                    progress += " ";
                }                  
            }
            progress += "] ";
            progress += percentage.ToString() + "%";
            
            Console.WriteLine($"Thread {Number}:{progress}");
        }
    }
}

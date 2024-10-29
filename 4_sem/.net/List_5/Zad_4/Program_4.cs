using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace Zad_4
{
    public static class TaskExtensions
    {
        public static HttpClient client = new HttpClient();
        public static TaskAwaiter<string> GetAwaiter(this string url)
        {
            //return client.GetStringAsync(url).GetAwaiter();//

            //string content = "";
            
                //var result = client.GetAsync(url).Result;
                //return result.Content.ReadAsStringAsync().GetAwaiter();
                //content += result.StatusCode;
                return client.GetAsync(url)
                    .ContinueWith(
                        t =>
                            t.Result.Content.ReadAsStringAsync()).Unwrap().GetAwaiter();
            
            //return content;

        }


    }
    class Program_4
    {
        
        static void Main(string[] args)
        {
        }
    }
}

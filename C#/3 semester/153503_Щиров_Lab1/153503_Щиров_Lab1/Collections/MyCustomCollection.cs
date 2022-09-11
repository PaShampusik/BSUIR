using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Reflection.Metadata;
using System.Text;
using System.Threading.Tasks;
using _153503_Щиров_Lab1.Interfaces;


namespace _153503_Щиров_Lab1.Collections
{
    abstract internal class MyCustomCollection<T> : ICustomCollection<T> where T : IComparable
    {
        public MyCustomCollection(Node<T> node)
        {
            
            Head = node;
        }
        public MyCustomCollection()
        {
            
        }
        public int Cursor
        {
            get;
            set;
        }
        private Node<T>? Head
        {
            get;
            set;
        }
            
        public void Reset()
        {
            Cursor = 0;
        }
        public void Next()
        {
            Cursor += 1;
        }
        
        public T Current()
        {
            Node<T>? buf = new Node<T>();
            buf = Head;
            for (int i = 0; i < Cursor; i++)
            {
                buf = buf.Next;
            }
            return buf.Data;            
        }

      

        public void Add(T item)
        {
            if (Head.Data == null)
            {
                Head.Data = item;
            }
            else
            {
                Node<T> buf = new Node<T>();
                buf = Head;
                while (buf.Next != null)
                {
                    buf = buf.Next;
                }
                buf.Next = new Node<T>();
                buf.Next.Data = item;
                buf.Next.Prev = buf;
            }
        }

        public void Remove(T item)
        {
            Node<T> buf = new Node<T>();
            buf = Head;
            
            while(buf.Data!.CompareTo(item) == 0)
            {
                buf = buf.Next;               
            }
            if (buf == Head)
            {
                Head = null;
            }else if(buf.Next == null)
            {
                buf.Prev.Next = null;                
            }else if(buf.Next != null)
            {
                buf.Prev.Next = buf.Next;
                buf.Next.Prev = buf.Prev;
            }
        }

        public T RemoveCurrent()
        {
            Node<T>? buf = new Node<T>();
            buf = Head;
            for (int i = 0; i < Cursor; i++)
            {
                buf = buf.Next;
            }

            T? data = buf.Data;
            Remove(buf.Data);
            return data;            
        }

        public int Count
        {
            get
            {
                Node<T>? buf = new Node<T>();
                buf = Head;
                int count = 0;
                while(buf.Next != null)
                {
                    buf = buf.Next;
                    count++;
                }
                return count;
            }           
        }

        public T this[int index] {
            get
            {
                Node<T>? buf = new Node<T>();
                buf = Head;
                for (int i = 0; i < index; i++)
                {
                    buf = buf.Next;                   
                }
                return buf.Data;
            }               
            set
            {
                Node<T>? buf = new Node<T>();
                buf = Head;
                for (int i = 0; i < index; i++)
                {
                    buf = buf.Next;
                }
                buf.Data = value;
            }
        }
    }
    
    class Node<T>
    {
        public T? Data { get; set; }
        public Node<T>? Next { get; set; }
        
        public Node<T>? Prev { get; set; }
    }
}

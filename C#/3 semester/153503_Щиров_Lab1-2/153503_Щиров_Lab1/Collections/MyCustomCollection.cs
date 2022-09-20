using System;
using System.Collections;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Reflection.Metadata;
using System.Text;
using System.Threading.Tasks;
using _153503_Щиров_Lab1.Interfaces;


namespace _153503_Щиров_Lab1.Collections
{
    internal class MyCustomCollection<T> : ICustomCollection<T> where T : IComparable
    {
        public MyCustomCollection(Node<T> node)
        {
            Head = node;
        }
        public MyCustomCollection()
        {
            Head = new Node<T>();
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

        public bool is_exist(T data)
        {
            Node<T>? buf = new Node<T>();
            buf = Head;
            while(buf != null)
            {
                if (buf.Data.Equals(data))
                {
                    return true;
                }               
                buf = buf.Next;
            }
            return false;
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
                buf.Next = new Node<T>(item);
                buf.Next.Prev = buf;
            }


        }

        public Node<T> get_next()
        {

            Node<T> buf = new Node<T>();
            buf = Head;
            for (int i = 0; i < Cursor; i++)
            {
                buf = buf.Next;
            }
            return buf;

        }

        public void Remove(T item)
        {
            Node<T> buf = new Node<T>();
            buf = Head;

            while (!buf!.Data!.Equals(item))
            {
                buf = buf.Next;
                if (buf == null)
                {
                    throw new WrongItemException();
                }
            }
            if (buf == Head)
            {
                Head = Head.Next;
            }
            else if (buf.Next == null)
            {
                buf.Prev.Next = null;
            }
            else if (buf.Next != null)
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
                while (buf.Next != null)
                {
                    buf = buf.Next;
                    count++;
                }
                return count;
            }
        }



        public T this[int index]
        {
            get
            {
                if (index < 0 || index > Count)
                {
                    throw new IndexOutOfRangeException();
                }
                Node<T> buf = new Node<T>();
                buf = Head;
                for (int i = 0; i < index; i++)
                {
                    if (buf.Next != null)
                    {
                        buf = buf.Next;
                    }

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

        public IEnumerator<T>? GetEnumerator()
        {
            Node<T>? buf = new Node<T>();
            buf = Head;
            while(buf != null)
            {
                yield return buf.Data;
                buf = buf.Next;               
            }
            
        }
        
        public sealed class WrongItemException : SystemException
        {
            
            public WrongItemException()
            {
                Console.WriteLine("That item doesnt exist");
            }
        
    }
    }
    
    

    /*class CollectionEnumerator<T> : IEnumerator<T>
    {
        public T Current
        {
            
        }

        object IEnumerator.Current => throw new NotImplementedException();

        public void Dispose()
        {
            throw new NotImplementedException();
        }

        public bool MoveNext()
        {
            throw new NotImplementedException();
        }

        public void Reset()
        {
            throw new NotImplementedException();
        }
    }
*/


    class Node<T>
    {
        public T? Data { get; set; }
        public Node<T>? Next { get; set; }

        public Node<T>? Prev { get; set; }

        public T get_price()
        {
            return this.Next.Next.Data;
        }

        public T get_name()
        {
            return this.Next.Data;
        }

        public T? GetData()
        {
            
                return Data;
            
        }

        public Node()
        {
            Data = default(T);
            Next = null;
            Prev = null;
        }
        
        public Node(T data)
        {
            Data = data;
            Next = null;
            Prev = null;
        }
    }

 



}
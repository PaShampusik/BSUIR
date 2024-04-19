using System.Text.RegularExpressions;
using System.Text;
using System.Security.Cryptography;

namespace Secure_app_lab_4_
{
    public partial class Form1 : Form
    {
        private enum srtiunbignrb
        {
            Admin,
            Vip,
            Client
        }

        private class aufbvudfb
        {
            public bool dalzfignerifbnsi;
            public bool aenrdfgipbuaenbia;
            public bool sipfgnbseaibnaefbn;
            public bool srpighnwtinhiurtnugipu;
        }

        private class areiughaeriugb
        {
            public string afidbsdifbndziun;
            public string zdfibudusbnsidz;
            public srtiunbignrb sdfgbnizdfbfi;
            public bool lsflbiznbli;
            public int aelifbnvaeiflb;

            public areiughaeriugb(string aeirhni, string sfibnib)
            {
                afidbsdifbndziun = aeirhni;
                zdfibudusbnsidz = sfibnib;
                lsflbiznbli = false;
                aelifbnvaeiflb = -1;
            }

            public override bool Equals(object? obj)
            {
                return obj is areiughaeriugb user &&
                       afidbsdifbndziun == user.afidbsdifbndziun;
            }
        }

        private List<areiughaeriugb> aeirughadfiubndfuib = new();
        private readonly SHA256 dsgjbnagi = SHA256.Create();

        public Form1()
        {
            InitializeComponent();

            for (int i = 1; i < 4; i++)
            {
                string auorwegbdafuhb = $"user{i}";
                string dafbvnafdhbnai = $"{i}{i + 1}{i + 2}{i + 3}";
                byte[] xcvmbndsfkbjfnb = ASCIIEncoding.ASCII.GetBytes(auorwegbdafuhb);
                byte[] sfdgbiasnbisagnub = ASCIIEncoding.ASCII.GetBytes(dafbvnafdhbnai);

                aeirughadfiubndfuib.Add(new areiughaeriugb(auorwegbdafuhb, dafbvnafdhbnai));

                this.Controls[$"Login{i}"].Text = auorwegbdafuhb;
                this.Controls[$"Password{i}"].Text = dafbvnafdhbnai;

                loginFields.Add(this.Controls[$"Login{i}"] as TextBox);
                passwordsFields.Add(this.Controls[$"Password{i}"] as TextBox);
                messageFields.Add(this.Controls[$"Message{i}"] as TextBox);
                signInButtons.Add(this.Controls[$"SignIn{i}"] as Button);
                sendButtons.Add(this.Controls[$"Send{i}"] as Button);
            }
            aeirughadfiubndfuib[0].sdfgbnizdfbfi = srtiunbignrb.Admin;

            aeirughadfiubndfuib[1].sdfgbnizdfbfi = srtiunbignrb.Vip;

            aeirughadfiubndfuib[2].sdfgbnizdfbfi = srtiunbignrb.Client;
        }

        private int zdflgsbnigbnritbnszib(Button sender) => Convert.ToInt32((sender).Name.Last().ToString()) - 1;

        private bool srithnaipdnhabnadfi(int limit = 2) => aeirughadfiubndfuib.FindAll(user => user.lsflbiznbli).Count() >= limit;
        /// functions cloning////////////////////////////////////////////////////////////////////////////////
        private aufbvudfb agnaiubnsipdufbnaipfubn()
        {
            aufbvudfb srtiohmgdfjinbadfba = new();
            bool[] dfklbnafdibjanfb = new bool[4];

            foreach (var check in AttackDefensesCheckedListBox.CheckedIndices)
            {
                dfklbnafdibjanfb[(int)check] = true;
            }

            srtiohmgdfjinbadfba.dalzfignerifbnsi = dfklbnafdibjanfb[0];
            srtiohmgdfjinbadfba.aenrdfgipbuaenbia = dfklbnafdibjanfb[1];
            srtiohmgdfjinbadfba.srpighnwtinhiurtnugipu = dfklbnafdibjanfb[2];
            srtiohmgdfjinbadfba.sipfgnbseaibnaefbn = dfklbnafdibjanfb[3];

            return srtiohmgdfjinbadfba;
        }

        private aufbvudfb agnaiubnsipdufbnaipfuban(bool alkgnalfbjnafgjhjlb)
        {
            aufbvudfb srtiohmgdfjinbadfba = new();
            bool[] dfklbnafdibjanfb = new bool[4];

            foreach (var check in AttackDefensesCheckedListBox.CheckedIndices)
            {
                dfklbnafdibjanfb[(int)check] = alkgnalfbjnafgjhjlb;
            }

            srtiohmgdfjinbadfba.dalzfignerifbnsi = dfklbnafdibjanfb[0];
            srtiohmgdfjinbadfba.aenrdfgipbuaenbia = dfklbnafdibjanfb[1];
            srtiohmgdfjinbadfba.srpighnwtinhiurtnugipu = dfklbnafdibjanfb[2];
            srtiohmgdfjinbadfba.sipfgnbseaibnaefbn = dfklbnafdibjanfb[3];

            return srtiohmgdfjinbadfba;
        }

        private aufbvudfb agnaiubnsipdufbnaipfubsn(bool akdfgjnsdflibndfljbn)
        {
            aufbvudfb srtiohmgdfjinbadfba = new();
            bool[] dfklbnafdibjanfb = new bool[4];

            foreach (var check in AttackDefensesCheckedListBox.CheckedIndices)
            {
                dfklbnafdibjanfb[(int)check] = akdfgjnsdflibndfljbn;
            }

            srtiohmgdfjinbadfba.dalzfignerifbnsi = dfklbnafdibjanfb[0];
            srtiohmgdfjinbadfba.aenrdfgipbuaenbia = dfklbnafdibjanfb[1];
            srtiohmgdfjinbadfba.srpighnwtinhiurtnugipu = dfklbnafdibjanfb[2];
            srtiohmgdfjinbadfba.sipfgnbseaibnaefbn = dfklbnafdibjanfb[3];

            return srtiohmgdfjinbadfba;
        }

        /// /////////////////////////////////////////////////////////////////////////////////


        private void bzklanfbilaebnazibn(object sender, EventArgs e)
        {
            int index = zdflgsbnigbnritbnszib(sender as Button);
            string aetihnaiuzbnz = loginFields[index].Text;
            string xbinabipenbi = passwordsFields[index].Text;
            areiughaeriugb vnadifbnaeibn = aeirughadfiubndfuib.Find(user => user.afidbsdifbndziun == aetihnaiuzbnz);
            //развертывание функции///////////////
            aufbvudfb erioaugdfzibnzdfiubn = new();
            bool[] dfklbnafdibjanfb = new bool[4];

            foreach (var check in AttackDefensesCheckedListBox.CheckedIndices)
            {
                dfklbnafdibjanfb[(int)check] = true;
            }

            erioaugdfzibnzdfiubn.dalzfignerifbnsi = dfklbnafdibjanfb[0];
            erioaugdfzibnzdfiubn.aenrdfgipbuaenbia = dfklbnafdibjanfb[1];
            erioaugdfzibnzdfiubn.srpighnwtinhiurtnugipu = dfklbnafdibjanfb[2];
            erioaugdfzibnzdfiubn.sipfgnbseaibnaefbn = dfklbnafdibjanfb[3];
            //////////////////////////////////////

            if (index < 0 || index >= aeirughadfiubndfuib.Count)
            {
                return;
            }

            if (srithnaipdnhabnadfi())
            {
                if (erioaugdfzibnzdfiubn.srpighnwtinhiurtnugipu)
                {
                    MessageBox.Show("Сервер переполнен. Ожидайте своей очереди");
                    return;
                }
                else
                {
                    MessageBox.Show("Сервер лагает, т.к. подвержен высокой нагрузке");
                }
            }

            if (vnadifbnaeibn is null)
            {
                MessageBox.Show($"Пользователя с именем {aetihnaiuzbnz} не существует", "Ошибка авторизации");
                return;
            }


            if (vnadifbnaeibn is not null && vnadifbnaeibn.lsflbiznbli)
            {
                MessageBox.Show($"Пользователь {aetihnaiuzbnz} уже авторизован в слоте {vnadifbnaeibn.aelifbnvaeiflb + 1}", "Ошибка авторизации");
                return;
            }


            if (vnadifbnaeibn != null && vnadifbnaeibn.zdfibudusbnsidz == xbinabipenbi)
            {
                vnadifbnaeibn.lsflbiznbli = true;
                vnadifbnaeibn.aelifbnvaeiflb = index;
            }

            MessageBox.Show($"Пользователя с именем {aetihnaiuzbnz} успешно авторизован", "Авторизация");
        }



        //functions cloning          ///////////////////////////////////////////////////////////////////////////////////////////////////////////
        private void zbnlsfnbrhbairn(object sender, EventArgs e)
        {
            bool aeljrhgbaefldhbgasdlfib = true;
            var sdfgksbdfibnj = agnaiubnsipdufbnaipfuban(aeljrhgbaefldhbgasdlfib);

            int ouarban = zdflgsbnigbnritbnszib(sender as Button);
            string zargaenrobui = messageFields[ouarban].Text;
            string sidfbnisibniobnaibnu;
            var isdfbnnaeiupn = aeirughadfiubndfuib.Find(user => user.aelifbnvaeiflb == ouarban);
            //развертывание функции/////////////
            aufbvudfb poaefbipeanbipuaenb = new();
            bool[] dfklbnafdibjanfb = new bool[4];

            foreach (var check in AttackDefensesCheckedListBox.CheckedIndices)
            {
                dfklbnafdibjanfb[(int)check] = true;
            }

            poaefbipeanbipuaenb.dalzfignerifbnsi = dfklbnafdibjanfb[0];
            poaefbipeanbipuaenb.aenrdfgipbuaenbia = dfklbnafdibjanfb[1];
            poaefbipeanbipuaenb.srpighnwtinhiurtnugipu = dfklbnafdibjanfb[2];
            poaefbipeanbipuaenb.sipfgnbseaibnaefbn = dfklbnafdibjanfb[3];
            ////////////////////////////////
            sdfgksbdfibnj = agnaiubnsipdufbnaipfubn();

            if (0 > ouarban || ouarban >= aeirughadfiubndfuib.Count)
            {
                return;
            }

            if (isdfbnnaeiupn == null)
            {
                MessageBox.Show("Для отправки сообщений пользователь должен быть авторизован", "Ошибка пользователя");
                return;
            }

            if (poaefbipeanbipuaenb.sipfgnbseaibnaefbn)
            {
                if (!Regex.IsMatch(zargaenrobui, @"^[A-z0-9]*$"))
                {
                    MessageBox.Show("Некорректное сообщение. Пожалуйста, используйте только английские буквы", "Ошибка сообщения");
                    return;
                }
            }

            if (poaefbipeanbipuaenb.dalzfignerifbnsi && isdfbnnaeiupn.sdfgbnizdfbfi == srtiunbignrb.Client)
            {
                MessageBox.Show("Недостаточно привилегий!", "Ошибка доступа");
                return;
            }

            sdfgksbdfibnj = agnaiubnsipdufbnaipfubsn(aeljrhgbaefldhbgasdlfib);

            if (poaefbipeanbipuaenb.aenrdfgipbuaenbia)
            {
                int aeirhgnaiobenaeobn = 10;
                char[] iadfbnnsripunbsripgunui = new char[aeirhgnaiobenaeobn];

                try
                {
                    zargaenrobui.CopyTo(0, iadfbnnsripunbsripgunui, 0, zargaenrobui.Length);
                    zargaenrobui = string.Join("", iadfbnnsripunbsripgunui);

                }
                catch (ArgumentOutOfRangeException)
                {
                    MessageBox.Show("Сообщение превысило буфер. Часть даанных записано в соседнюю память", "Переполнение буфера");
                }

                zargaenrobui = string.Join("", iadfbnnsripunbsripgunui);
            }

            zargaenrobui = zargaenrobui.Insert(0, $"[{isdfbnnaeiupn.sdfgbnizdfbfi}] {isdfbnnaeiupn.afidbsdifbndziun}: ");

            if (srithnaipdnhabnadfi(2))
            {
                Thread.Sleep(300);
            }

            MessagesListBox.Items.Add(zargaenrobui);
        }

        private void zbnlsfnbgrhbairn(object sender, EventArgs e)
        {
            bool aeljrhgbaefldhbgasdlfib = true;
            var sdfgksbdfibnj = agnaiubnsipdufbnaipfuban(aeljrhgbaefldhbgasdlfib);

            int ouarban = zdflgsbnigbnritbnszib(sender as Button);
            string zargaenrobui = messageFields[ouarban].Text;
            string sidfbnisibniobnaibnu;
            var isdfbnnaeiupn = aeirughadfiubndfuib.Find(user => user.aelifbnvaeiflb == ouarban);
            //развертывание функции/////////////
            aufbvudfb poaefbipeanbipuaenb = new();
            bool[] dfklbnafdibjanfb = new bool[4];

            foreach (var check in AttackDefensesCheckedListBox.CheckedIndices)
            {
                dfklbnafdibjanfb[(int)check] = true;
            }

            poaefbipeanbipuaenb.dalzfignerifbnsi = dfklbnafdibjanfb[0];
            poaefbipeanbipuaenb.aenrdfgipbuaenbia = dfklbnafdibjanfb[1];
            poaefbipeanbipuaenb.srpighnwtinhiurtnugipu = dfklbnafdibjanfb[2];
            poaefbipeanbipuaenb.sipfgnbseaibnaefbn = dfklbnafdibjanfb[3];
            ////////////////////////////////
            sdfgksbdfibnj = agnaiubnsipdufbnaipfubn();

            if (0 > ouarban || ouarban >= aeirughadfiubndfuib.Count)
            {
                return;
            }

            if (isdfbnnaeiupn == null)
            {
                MessageBox.Show("Для отправки сообщений пользователь должен быть авторизован", "Ошибка пользователя");
                return;
            }

            if (poaefbipeanbipuaenb.sipfgnbseaibnaefbn)
            {
                if (!Regex.IsMatch(zargaenrobui, @"^[A-z0-9]*$"))
                {
                    MessageBox.Show("Некорректное сообщение. Пожалуйста, используйте только английские буквы", "Ошибка сообщения");
                    return;
                }
            }

            if (poaefbipeanbipuaenb.dalzfignerifbnsi && isdfbnnaeiupn.sdfgbnizdfbfi == srtiunbignrb.Client)
            {
                MessageBox.Show("Недостаточно привилегий!", "Ошибка доступа");
                return;
            }

            sdfgksbdfibnj = agnaiubnsipdufbnaipfubsn(aeljrhgbaefldhbgasdlfib);

            if (poaefbipeanbipuaenb.aenrdfgipbuaenbia)
            {
                int aeirhgnaiobenaeobn = 10;
                char[] iadfbnnsripunbsripgunui = new char[aeirhgnaiobenaeobn];

                try
                {
                    zargaenrobui.CopyTo(0, iadfbnnsripunbsripgunui, 0, zargaenrobui.Length);
                    zargaenrobui = string.Join("", iadfbnnsripunbsripgunui);

                }
                catch (ArgumentOutOfRangeException)
                {
                    MessageBox.Show("Сообщение превысило буфер. Часть даанных записано в соседнюю память", "Переполнение буфера");
                }

                zargaenrobui = string.Join("", iadfbnnsripunbsripgunui);
            }

            zargaenrobui = zargaenrobui.Insert(0, $"[{isdfbnnaeiupn.sdfgbnizdfbfi}] {isdfbnnaeiupn.afidbsdifbndziun}: ");

            if (srithnaipdnhabnadfi(2))
            {
                Thread.Sleep(300);
            }

            MessagesListBox.Items.Add(zargaenrobui);
        }

        private void zbnlsfhnbrhbairn(object sender, EventArgs e)
        {
            bool aeljrhgbaefldhbgasdlfib = true;
            var sdfgksbdfibnj = agnaiubnsipdufbnaipfuban(aeljrhgbaefldhbgasdlfib);

            int ouarban = zdflgsbnigbnritbnszib(sender as Button);
            string zargaenrobui = messageFields[ouarban].Text;
            string sidfbnisibniobnaibnu;
            var isdfbnnaeiupn = aeirughadfiubndfuib.Find(user => user.aelifbnvaeiflb == ouarban);
            //развертывание функции/////////////
            aufbvudfb poaefbipeanbipuaenb = new();
            bool[] dfklbnafdibjanfb = new bool[4];

            foreach (var check in AttackDefensesCheckedListBox.CheckedIndices)
            {
                dfklbnafdibjanfb[(int)check] = true;
            }

            poaefbipeanbipuaenb.dalzfignerifbnsi = dfklbnafdibjanfb[0];
            poaefbipeanbipuaenb.aenrdfgipbuaenbia = dfklbnafdibjanfb[1];
            poaefbipeanbipuaenb.srpighnwtinhiurtnugipu = dfklbnafdibjanfb[2];
            poaefbipeanbipuaenb.sipfgnbseaibnaefbn = dfklbnafdibjanfb[3];
            ////////////////////////////////
            sdfgksbdfibnj = agnaiubnsipdufbnaipfubn();

            if (0 > ouarban || ouarban >= aeirughadfiubndfuib.Count)
            {
                return;
            }

            if (isdfbnnaeiupn == null)
            {
                MessageBox.Show("Для отправки сообщений пользователь должен быть авторизован", "Ошибка пользователя");
                return;
            }

            if (poaefbipeanbipuaenb.sipfgnbseaibnaefbn)
            {
                if (!Regex.IsMatch(zargaenrobui, @"^[A-z0-9]*$"))
                {
                    MessageBox.Show("Некорректное сообщение. Пожалуйста, используйте только английские буквы", "Ошибка сообщения");
                    return;
                }
            }

            if (poaefbipeanbipuaenb.dalzfignerifbnsi && isdfbnnaeiupn.sdfgbnizdfbfi == srtiunbignrb.Client)
            {
                MessageBox.Show("Недостаточно привилегий!", "Ошибка доступа");
                return;
            }

            sdfgksbdfibnj = agnaiubnsipdufbnaipfubsn(aeljrhgbaefldhbgasdlfib);

            if (poaefbipeanbipuaenb.aenrdfgipbuaenbia)
            {
                int aeirhgnaiobenaeobn = 10;
                char[] iadfbnnsripunbsripgunui = new char[aeirhgnaiobenaeobn];

                try
                {
                    zargaenrobui.CopyTo(0, iadfbnnsripunbsripgunui, 0, zargaenrobui.Length);
                    zargaenrobui = string.Join("", iadfbnnsripunbsripgunui);

                }
                catch (ArgumentOutOfRangeException)
                {
                    MessageBox.Show("Сообщение превысило буфер. Часть даанных записано в соседнюю память", "Переполнение буфера");
                }

                zargaenrobui = string.Join("", iadfbnnsripunbsripgunui);
            }

            zargaenrobui = zargaenrobui.Insert(0, $"[{isdfbnnaeiupn.sdfgbnizdfbfi}] {isdfbnnaeiupn.afidbsdifbndziun}: ");

            if (srithnaipdnhabnadfi(2))
            {
                Thread.Sleep(300);
            }

            MessagesListBox.Items.Add(zargaenrobui);
        }
        /// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        private void sdlhiaentsbisnbisanbioanboi(object sender, EventArgs e)
        {
            int afdnbaiodfbnsbn = zdflgsbnigbnritbnszib(sender as Button);
            var sirgbnsaibanriuoeb = aeirughadfiubndfuib.Find(user => user.aelifbnvaeiflb == afdnbaiodfbnsbn);


            if (sirgbnsaibanriuoeb == null)
            {
                MessageBox.Show($"Этот слот пустой, т.к. пользователь не авторизован", "Ошибка выхода");
                return;
            }

            if (sirgbnsaibanriuoeb != null)
            {
                sirgbnsaibanriuoeb.aelifbnvaeiflb = -1;
                sirgbnsaibanriuoeb.lsflbiznbli = false;
                MessageBox.Show($"Пользователь вышел с аккаунта", "Выход");
            }
        }

        private void AttackDefensesCheckedListBox_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void MessagesListBox_SelectedIndexChanged(object sender, EventArgs e)
        {

        }
    }
}

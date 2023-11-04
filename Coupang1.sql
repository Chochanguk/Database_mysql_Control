set global log_bin_trust_function_creators = 1;

CREATE DATABASE Coupang1 default CHARACTER SET UTF8;
show databases; 
use Coupang1;

create table User1(
ID varchar(20),
Phone_number varchar(20),
Email_address varchar(80),
Name char(20),
primary key(ID));

create table Customer(
Customer_number int,
Resident_number char(20),
Address varchar(80),
ID varchar(20),
primary key(Customer_number),
Foreign key(ID) references User1(ID));

create table Manufacturer(
ID varchar(20),
Business_number varchar(20),
Address varchar(80),
Bank_identification varchar(30),
Telephone_number varchar(20),
Account_number varchar(40),
Deposit_accont_name char(20),
primary key(Business_number),
foreign key(ID) references User1(ID));

create table Product(
Product_number varchar(10),
Product_unitprice int,
Product_classification varchar(10),
Product_quantity int,
Business_number varchar(20),
primary key(Product_number),
foreign key(Business_number) references Manufacturer(Business_number));

create table Payment(
Customer_number int,
Payment_method char(10),
Payment_account varchar(40),
Manufacturer_account_number varchar(40),
Receipt_issuance varchar(10),
Bank_code varchar(10),
foreign key(Customer_number) references Customer(Customer_number));

create table Order1(
Order_number varchar(15),
Customer_number int,
Order_date varchar(8),
Shipping_address varchar(80),
Shipping_phone_number varchar(20),
primary key(Order_number),
foreign key(Customer_number) references Customer(Customer_number));

create table Delivery(
Shipping_number varchar(20),
Order_number varchar(15),
Courier_Business_number varchar(20),
Delivery_date varchar(8));

select * from User1;
insert into User1 values('0001', '01012345678', '123@dgu.ac.kr', '홍길동');
insert into User1 values('0002', '01012345679', '456@dgu.ac.kr', '김동국');
insert into User1 values('0003', '01012345680', '789@dgu.ac.kr', '최정통');
insert into User1 values('0004', '01012345681', '910@dgu.ac.kr', '이데베');
insert into User1 values('0005', '01012345682', '111@dgu.ac.kr', '박이일');
insert into User1 values('0006', '01012345683', '121@dgu.ac.kr', '민일구');
select * from User1;

select * from Customer;
insert into Customer values(1, '010212', '서울특별시 송파구', '0001');
insert into Customer values(2, '010527', '서울특별시 종로구', '0003');
insert into Customer values(3, '981204', '서울특별시 강남구', '0005');
select * from Customer;

select * from Manufacturer;
insert into Manufacturer values('0002', '0123456789', '서울특별시 도봉구', '1234', '0212345678','91011', '김동국');
insert into Manufacturer values('0004', '0123456710', '서울특별시 서초구', '1234', '0212345689','30284', '이데베');
insert into Manufacturer values('0006', '0123453892', '서울특별시 노원구', '1319', '0212397493','93042', '민일구');
select * from Manufacturer;

select * from Product;
insert into Product values('0000001', 1200, '식품', 100, '0123456789');
insert into Product values('0000100', 30000, '의류', 35, '0123456710');
insert into Product values('0010000', 100000, '가전제품', 15, '0123453892');
select * from Product;

select * from User1
where name='김동국';

set @name='가전제품';
select  * from Product
where Product_classification in (@name);


select * from customer natural join User1;
select * from manufacturer natural join User1;

set @where_price=40;
select product_number from product
where product_unitprice>
some(select product_unitprice from product
where product_quantity>(@where_price));
set @a='%67%';
set @b='%이%';
(select name from User1 where phone_number like (@a)) 
union (select Deposit_accont_name from Manufacturer where Deposit_accont_name like (@b));
select ID from Use1 where ID like '%ID%';
set @where_quantity=100;
set @name='가전제품';
select avg(product_unitprice) from product
where product_quantity=(@where_quantity) or product_classification=(@name);

select product_number, avg(product_quantity) from product group by product_number;

select product_number from product where product_unitprice>all(select product_unitprice from product where product_quantity>40);

select product_number from product where product_unitprice>some(select product_unitprice from product where product_quantity<40);

set @user1_name='이데베';
select distinct S.name from user1 as S
where exists(
select deposit_accont_name from manufacturer where deposit_accont_name=(@user1_name));

SELECT * FROM Product LIMIT 0;


set @where_price=40;
select distinct S.Business_number from manufacturer as S
where exists((select Business_number from product where product_quantity>(@where_price))
union(select T.Business_number from Product as T where S.Business_number=T.Business_number)); 

select product_number from product
where product_unitprice<10000;

select product_number from product
where ((product_classification='식품') and (product_quantity>0));

select * from user1 natural join customer;

select telephone_number from Manufacturer as T
where(T.business_number=(select S.business_number from product as S
where product_number='0000001'));
-- call procedure
call Numbers_of_User(); 
-- use fucntion
select sum_of_Product();
select sum_of_Product() /count(Product_number) from Product;

DELETE from User1 where ID='changuk0308';


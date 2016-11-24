#define BASEFUNCTION(fname) CallLater *fname(CallLater *cl, CellTable *ct)

BASEFUNCTION(inc)
{
	(*(ct->pointer))++;
	return cl->next;
}

BASEFUNCTION(dec)
{
	(*(ct->pointer))--;
	return cl->next;
}

BASEFUNCTION(incpt)
{
	ct->pointer ++;
	return cl->next;
}

BASEFUNCTION(decpt)
{
	ct->pointer --;
	return cl->next;
}

BASEFUNCTION(prnt)
{
	printf("%c", *(ct->pointer));
	return cl->next;
}

BASEFUNCTION(prntv)
{
	printf("%d\n", *(ct->pointer));
	return cl->next;
}

BASEFUNCTION(loop)
{
	if(*(ct->pointer) != 0) return cl->fail;
	else return cl->next;
}

BASEFUNCTION(skip)
{
	return cl->next;
}

BASEFUNCTION(end)
{
	return NULL;
}
<?php  $this->load->view('header');  ?>
<?php  $this->load->view('navbar');  ?>
<?php  $this->load->helper('url');  ?>

<div class="row">
<div class="span12">
<h2>User Management</h2>
<p style="margin-top: 25px;"> </p>
<ul class="nav nav-tabs ">
   <li class="active"><a href="#">General</a></li>
   <li><a href="#">Admin</a></li>
   <li>
      <form class="form-search admin-tabs-search" action="#" method="post" accept-charset="utf-8">
      <i class="icon-search admin-tabs-search-icon"></i><input class="" type="text" name="key" value="">
      </form>
   </li>
</ul>


</div>
</div>

<?php $this->load->view('footer');  ?>
